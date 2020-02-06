#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utility.h"

// Represents actions user can specify at the command line
enum Action {
    print_col_type,
    print_col_idx,
    check_missing_idx,
    unspecified,
};

// Represents user specified configuration
// parsed from command line args
class Configuration {
public:
    int argc;
    char** argv; // [NOT-OWNED]
    char* filename = nullptr; // [OWNED]

    size_t read_start_index = 0;
    size_t bytes_to_read = 0;
    bool bytes_to_read_specified = false;

    Action action = unspecified;
    size_t action_column = 0;
    size_t action_row = 0;
    
    Configuration(int argc, char** argv) {
        this->argc = argc;
        this->argv = argv;
    }

    ~Configuration() {
        delete[] this->filename;
    }

    // matches given str with action enum
    Action match_action(char* str) {
        if (strcmp(str, "-print_col_type") == 0 ) {
            return print_col_type;
        } else if (strcmp(str, "-print_col_idx") == 0) {
            return print_col_idx;
        } else if (strcmp(str, "-is_missing_idx") == 0) {
            return check_missing_idx;
        }
        return unspecified;
    }

    // parses command line arguments
    // @returns 0 on success, -1 on failure
    int parse() {
        bool read_start_index_set = false;
        for (size_t i = 1; i < argc; i++) {
            // flag must have value in bounds
            if (i == argc - 1) {
                return -1;
            }

            char* flag = this->argv[i];
            char* next_value = this->argv[i + 1];
            if (strcmp(flag, "-f") == 0) {
                // filename already specified
                if (this->filename) {
                    return -1;
                }

                // read in file name
                this->filename = new char[strlen(next_value)+1];
                strcpy(this->filename, next_value);
                i++;
            } else if (strcmp(flag, "-from") == 0) {
                // read start index specified, or invalid index
                if (read_start_index_set || !Utility::is_valid_uint(next_value)) {
                    return -1;
                }

                // read in starting position
                this->read_start_index = (size_t) atoll(next_value);
                read_start_index_set = true;
                i++;
            } else if (strcmp(flag, "-len") == 0) {
                // read end index specified, or invalid index
                if (this->bytes_to_read_specified || !Utility::is_valid_uint(next_value)) {
                    return -1;
                }

                // read in number of bytes to read
                this->bytes_to_read = (size_t) atoll(next_value);
                this->bytes_to_read_specified = true;
                i++;
            } else if (strcmp(flag, "-print_col_type") == 0) {
                // action already specified, or invalid index
                if (this->action != unspecified || !Utility::is_valid_uint(next_value)) {
                    return -1;
                }

                // read in action type, and col index
                this->action = print_col_type;
                this->action_column = (size_t) atoll(next_value);
                i++;
            } else if (strcmp(flag, "-print_col_idx") == 0 || strcmp(flag, "-is_missing_idx") == 0) {
                // action already specified, or argument out of bonds
                if (this->action != unspecified || i + 2 >= this->argc) {
                    return -1;
                }

                // invalid indicies given
                if (!Utility::is_valid_uint(next_value) || !Utility::is_valid_uint(argv[i + 2])) {
                    return -1;
                }
                this->action = this->match_action(flag);
                this->action_column = (size_t) atoll(next_value);
                this->action_row = (size_t) atoll(argv[i + 2]);
                i += 2;
            }
        }
        return this->filename ? 0 : -1;
    }
};