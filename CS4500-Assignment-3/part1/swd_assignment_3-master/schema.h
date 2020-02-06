#pragma once

#include <iostream> // REMOVE!
#include <vector>
#include "token.h"
#include "utility.h"
#include "debug.h" // REMOVE

// Schema class infers data-type representation
// from given tokens
class Schema {
public:
    static void merge_data(vector<vector<Token*>*>* dest, vector<vector<Token*>*>* src) {
        for (size_t i = 0; i < src->size(); i++) {
            vector<Token*>* column = dest->at(i);
            vector<Token*>* new_column = src->at(i);
            column->insert(column->end(), new_column->begin(), new_column->end());
            new_column->clear();
            delete new_column;
        }
        src->clear();
        delete src;
    }
    static void delete_record(vector<Token*>* record) {
        if (!record)
            return;
        for (size_t i = 0; i < record->size(); i++){
            delete record->at(i);
        }
        record->clear();
        delete record;
    }

    //deletes given data
    static void delete_data(vector<vector<Token*>*>* data) {
        if (!data)
            return;
        for (size_t i = 0; i < data->size(); i++) {
            vector<Token*>* record = data->at(i);
            Schema::delete_record(record);
        }
        data->clear();
        delete data;
    }

    static void delete_schema(vector<DataType>* schema) {
        if (!schema)
            return;
        schema->clear();
        delete schema;
    }
    
    static vector<DataType>* analyze_tokens_for_schema(vector<Token*>* tokens) {
        vector<DataType>* underlying_schema = new vector<DataType>();
        for (size_t i = 0; i < tokens->size(); i++) {
            Token* t = tokens->at(i);
            if (t->type == NONE)
                t->type = BOOL;
            underlying_schema->push_back(t->type);
        }
        return underlying_schema;
    }

    // detects whether line of tokens matches a given schema
    // also pads lines with empty tokens
    static bool match(vector<Token*>* tokens, vector<DataType>* schema) {
        bool atleast_one_match = false;
        if (tokens->size() == 0 || tokens->size() > schema->size()) {
            return false;
        }

        for (size_t i = 0; i < schema->size(); i++) {
            Token* token = tokens->at(i);
            DataType token_type = token->type;
            DataType schema_type = schema->at(i);
            if (i >= tokens->size()) {
                // pad with empty token
                tokens->push_back(new Token(nullptr, NONE));
            } else if (token_type != schema_type) {
                // check if type can be 'coerced' to schema type
                if (token->value != nullptr) { // empty values can be coerced to anything
                    if (schema_type == STRING && !Token::is_string(token->value)) {
                        return false;
                    } else if (schema_type == FLOAT) {
                        if (token_type != INTEGER && token_type != BOOL) {
                            return false;
                        }
                    } else if (schema_type == INTEGER && !Token::is_integer(token->value)) {
                        return false;
                    } else if (schema_type == BOOL && !Token::is_bool(token->value)) {
                        return false;
                    }   
                }
                token->type = schema_type;
                atleast_one_match = true;
            } else {
                atleast_one_match = true;
            }
        }
        return atleast_one_match;
    }

    // inserts a given line of tokens into destination,
    // in columnar format by a given schema
    static void insert_columnar(
        vector<Token*>* source,
        vector<vector<Token*>*>* destination, 
        vector<DataType>* schema
    ) {
        for (size_t i = 0; i < schema->size(); i++) {
            vector<Token*>* column = destination->at(i);
            column->push_back(source->at(i));
        }
    }
};