#pragma once

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <ctype.h>
#include <thread>

#include "buffer.h"
#include "cmdline.h"
#include "utility.h"
#include "token.h"
#include "schema.h"
#include "debug.h" // remove

using namespace std;

// max # of lines to read schema
const size_t LINES_TO_INFER_SCHEMA = 500;
const size_t PARSE_BATCH_SIZE = 20000; // must be evenly divisible by 2, using 2 threads

// Represents view of SOR data
class DataFrame {
private:
    // given file configuration [OWNED]
    Configuration* config = nullptr;
    // underlying memory buffer [OWNED]
    ByteBuffer* buffer = nullptr;
    // represents schema of data
    // Ex. [int, float, bool]
    vector<DataType>* schema = nullptr; // [OWNED]
    // data in columnar format
    // Ex.
    // [int, float, bool]
    // [int, float, bool]
    vector<vector<Token*>*>* data = nullptr; // [OWNED]
    size_t file_size = 0;
public:
    DataFrame(Configuration* config) {
        assert(config != nullptr);
        this->config = config;
        this->buffer = this->prepare_buffer(this->config);
    }

    ~DataFrame() {
        delete this->config;
        delete this->buffer;
        Schema::delete_schema(this->schema);
        Schema::delete_data(this->data);
    }

    // runs given action in input config
    // @pre caller needs to parse() before run()
    void run(char* output_buffer) {
        Action action = this->config->action;
        size_t action_col = this->config->action_column;
        size_t action_row = this->config->action_row;
        bool is_valid_column = action_col < this->schema->size();

        if (action == print_col_type) {
            if (is_valid_column) {
                DataType type = this->schema->at(action_col);
                sprintf(output_buffer, "%s", DATA_TYPE_TO_STRING[type]);
            }
        } else if (action == print_col_idx) {
            if (is_valid_column) {
                vector<Token*>* column = this->data->at(action_col);
                if (action_row < column->size()) {
                    column->at(action_row)->write_to_buff(output_buffer);
                }
            }
        } else if (action == check_missing_idx) {
            if (is_valid_column) {
                vector<Token*>* column = this->data->at(action_col);
                if (action_row < column->size()) {
                    bool is_missing = column->at(action_row)->value == nullptr;
                    sprintf(output_buffer, "%d", is_missing);
                }
            }
        }
    }

    static void process(
        vector<string*>* lines, 
        size_t start, size_t end, 
        vector<vector<Token*>*>* results,
        vector<DataType>* schema
    ) {
        for (size_t i = start; i < end; i++) {
            string* line = lines->at(i);
            vector<Token*>* record = Token::tokenize_line(line);
            if (record != nullptr && Schema::match(record, schema)) {
                Schema::insert_columnar(record, results, schema);
                record->clear();
                delete record;
            }
        }
    }

    vector<vector<Token*>*>* create_columnar_format(vector<DataType>* schema) {
        vector<vector<Token*>*>* df = new vector<vector<Token*>*>();
        for (size_t i = 0; i < schema->size(); i++) {
            df->push_back(new vector<Token*>());
        }
        return df;
    }

    // parses, tokenizes loaded file
    // @returns -1 on failure, 0 on success
    int parse() {
        // if read_start_index not 0, skip first line
        if (this->config->read_start_index != 0) {
            delete this->buffer->read_line();
        }

        // infer schema from select number of lines from file
        vector<string*>* lines = this->sample_lines(LINES_TO_INFER_SCHEMA);
        vector<vector<Token*>*>* sample_records = this->tokenize_lines(lines);
        this->schema = this->analyze_for_schema(sample_records);
        Schema::delete_data(sample_records);
        if (this->schema->size() == 0) {
            return -1; // no schema detected, quit early
        }
        
        // construct internal data representation based on schema
        this->data = this->create_columnar_format(this->schema);

        // tokenize rest of file, include in sample
        string* current_line = this->buffer->read_line();
        while(current_line) {
            lines->push_back(current_line);
            if (lines->size() == PARSE_BATCH_SIZE) {
                vector<vector<Token*>*>* t1_acc = this->create_columnar_format(this->schema);
                vector<vector<Token*>*>* t2_acc = this->create_columnar_format(this->schema);

                size_t segment_size = PARSE_BATCH_SIZE / 2;
                thread t1(&DataFrame::process, lines, 0, segment_size, t1_acc, this->schema);
                thread t2(&DataFrame::process, lines, segment_size, segment_size*2, t2_acc, this->schema);

                t1.join();
                t2.join();

                Schema::merge_data(this->data, t1_acc);
                Schema::merge_data(this->data, t2_acc);

                for (size_t i = 0; i < lines->size(); i++) {
                    delete lines->at(i);
                }
                lines->clear();
            }
            current_line = this->buffer->read_line();
        }

        if (lines->size() != 0) {
            DataFrame::process(lines, 0, lines->size(), this->data, this->schema);
            for (size_t i = 0; i < lines->size(); i++) {
                delete lines->at(i);
            }
            lines->clear();
        }
        delete lines;

        // if end # of bytes specified, and not total length of file, skip last line
        Configuration* config = this->config;
        if (config->bytes_to_read_specified && config->bytes_to_read != this->file_size) {
            for (size_t i = 0; i < this->data->size(); i++) {
                vector<Token*>* column = this->data->at(i);
                delete column->at(column->size() - 1);
                column->pop_back();
            }
        }
        return 0;
    }

private:
    // fetches a sample of content from file
    vector<string*>* sample_lines(size_t num_samples) {
        vector<string*>* sample = new vector<string*>();
        for (size_t i = 0; i < num_samples; i++) {
            string* line = this->buffer->read_line();
            if (!line) // end of file
                break;
            sample->push_back(line);
        }
        return sample;
    }

    vector<vector<Token*>*>* tokenize_lines(vector<string*>* lines) {
        vector<vector<Token*>*>* records = new vector<vector<Token*>*>();
        for (size_t i = 0; i < lines->size(); i++) {
            vector<Token*>* record = Token::tokenize_line(lines->at(i));
            if (record)
                records->push_back(record);
        }
        return records;
    }

    void absorb_new_schema(vector<DataType>* original_schema, vector<DataType>* new_schema) {
        for (size_t i = 0; i < original_schema->size(); i++) {
            DataType cur_type = original_schema->at(i);
            DataType inferred_type = new_schema->at(i);
            if (inferred_type == STRING) {
                // if a string is seen in any column, whole column is string
                original_schema->at(i) = STRING; 
            }
            bool should_be_promoted_to_float = (
                inferred_type == FLOAT &&
                (cur_type == INTEGER || cur_type == BOOL)
            );
            if (should_be_promoted_to_float) {
                // if float is seen, promote numeric types to float
                original_schema->at(i) = FLOAT;
            } else if (cur_type == NONE) {
                original_schema->at(i) = inferred_type;
            } else if (cur_type == BOOL) {
                original_schema->at(i) = inferred_type;
            }
        }
    }

    // detects longest schema
    vector<DataType>* analyze_for_schema(vector<vector<Token*>*>* records) {
        vector<DataType>* longest_schema = new vector<DataType>();
        for (size_t i = 0; i < records->size(); i++) {
            vector<Token*>* record = records->at(i);
            vector<DataType>* inferred_schema = Schema::analyze_tokens_for_schema(record);
            if (!inferred_schema)
                continue; // unable to infer schema from series of tokens
            if (!longest_schema) {
                longest_schema = inferred_schema;
            } else if (inferred_schema->size() > longest_schema->size()) {
                Schema::delete_schema(longest_schema);
                longest_schema = inferred_schema;
            } else if (inferred_schema->size() == longest_schema->size()) {
                // check to see if any types should be "promoted"
                this->absorb_new_schema(longest_schema, inferred_schema);
                Schema::delete_schema(inferred_schema);
            }
        }
        return longest_schema;
    }

    // analyze lines of tokens, include those that fit schema in data,
    // padding with None typed tokens if necessary
    void process_sample(
        vector<vector<Token*>*>* processed_lines,
        vector<vector<Token*>*>* unprocessed_lines, 
        vector<DataType>* schema
    ) {
        for (size_t i = 0; i < unprocessed_lines->size(); i++) {
            vector<Token*>* record = unprocessed_lines->at(i);
            if (Schema::match(record, schema)) {
                Schema::insert_columnar(record, processed_lines, schema);
                record->clear();
                delete record;
                unprocessed_lines->at(i) = nullptr;
            }
        }
    }

    // Opens a file
    FILE* open_file(char* filename) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            char failure_msg[256];
            sprintf(failure_msg, "Unable to open file: %s", filename);
            Utility::quit(failure_msg);
        }
        return file;
    }

    ByteBuffer* prepare_buffer(Configuration* config) {
        // open file, seek to specified index
        FILE* file = this->open_file(config->filename);
        int status_code = fseek(file, config->read_start_index, 0);
        assert(status_code == 0);

        size_t bytes_to_read;
        // determine total # of bytes to read, based on config
        if (config->bytes_to_read_specified) {
            bytes_to_read = config->bytes_to_read;
        } else {
             // fetch total file size: Referenced https://linux.die.net/man/2/fstat
            struct stat file_stat;
            fstat(fileno(file), &file_stat);
            this->file_size = file_stat.st_size;
            bytes_to_read = this->file_size;
        }
        return new ByteBuffer(file, bytes_to_read);
    }
};