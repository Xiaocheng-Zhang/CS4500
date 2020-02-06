#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "utility.h"

using namespace std;

const size_t MAX_STRING_LENGTH = 255;

// Represents accepted data types
enum DataType {
    BOOL,
    INTEGER,
    FLOAT,
    STRING,
    NONE
};

// Referenced: https://stackoverflow.com/questions/3342726/c-print-out-enum-value-as-text
const char* DATA_TYPE_TO_STRING[] = {
    "BOOL",
    "INTEGER",
    "FLOAT",
    "STRING",
    "NONE"
};

// Represents a parsed token from SOE
class Token {
public:
    string* value = nullptr;
    DataType type;
public:
    Token(string* value, DataType type) {
        this->value = value;
        this->type = type;
    }

    ~Token() {
        if (this->value) {
            delete this->value;
            this->value = nullptr;
        }
    }

    void write_to_buff(char* buff) {
        if (this->type == NONE || this->value == nullptr) {
            return;
        }
        sprintf(buff, "%s", this->value->c_str());
    }

    // parses a given string as a boolean
    // @returns nullptr on failure, Token on success
    static bool is_bool(string* str) {
       if (str->size() != 1) {
            return false;
        } else {
            char c = str->at(0);
            return c == '0' || c == '1';
        }
    }

    static bool is_integer(string* str) {
        if (str->size() == 0)
            return false;

        bool has_sign = false;
        bool has_atleast_one_digit = false;
        for (size_t i = 0; i < str->size(); i++) {
            char c = str->at(i);
            if (i == 0) {
                bool is_number = isdigit(c);
                // must be signed, or begin with digit
                if (c != '+' && c != '-' && !is_number) {
                    return false;
                }
                has_atleast_one_digit = is_number;
                has_sign = c == '+' || c == '-';
            } else {
                if (c == '.') {
                    return false;
                } else {
                    // otherwise must be contiguous digit
                    if (!isdigit(c)) {
                        return false;
                    }
                    has_atleast_one_digit = true;
                }
            }
        }

        if (str->size() == 2) { // should be a string, violates int/float/bool convention
            if (has_sign) {
                if (str->at(1) == '1' || str->at(1) == '0')
                    return false;
            }
        } else if (str->size() == 1) {
            if (str->at(0) == '1' || str->at(0) == '0') // bool
                return false;
        }
        return has_atleast_one_digit;
    }

    static bool is_float(string* str) {
        if (str->size() == 0)
            return false;

            bool has_sign, has_atleast_one_digit, has_decimal_point = false;
            for (size_t i = 0; i < str->size(); i++) {
                char c = str->at(i);
                if (i == 0) {
                    bool is_number = isdigit(c);
                    // must be signed, or begin with . or digit
                    if (c != '+' && c != '-' && c != '.' && !is_number) {
                        return false;
                    }
                    has_decimal_point = c == '.';
                    has_atleast_one_digit = is_number;
                    has_sign = c == '+' || c == '-';
                } else {
                    if (c == '.') {
                        // can only have 1 decimal point
                        if (has_decimal_point) {
                            return false;
                        }
                        has_decimal_point = true;
                    } else {
                        // otherwise must be contiguous digit
                        if (!isdigit(c)) {
                            return false;
                        }
                        has_atleast_one_digit = true;
                    }
                }
            }

            if (str->size() == 2) { // should be a string, violates int/float/bool convention
                if (has_sign) {
                    if (str->at(1) == '1' || str->at(1) == '0')
                        return false;
                }
            } else if (str->size() == 1) {
                if (str->at(0) == '1' || str->at(0) == '0') // bool
                    return false;
            }
            return has_decimal_point && has_atleast_one_digit;
    }

    static bool is_string(string* str) {
        if (str->size() > MAX_STRING_LENGTH)
            return false;

        bool begins_with_quote = false;
        for (size_t i = 0; i < str->size(); i++) {
            char c = str->at(i);
            if (i == 0) {
                begins_with_quote = c == '"';
            } else {
                bool is_quote = c == '"';
                if (is_quote && !begins_with_quote)
                    return false;
                if (is_quote && i != str->size() - 1) {
                    return false;
                }
            }
        }
        return true;
    }

    // parses a given string as a number
    // @returns nullptr on failure, Token on success
    static Token* parse_number(string* str) {
        if (Token::is_integer(str)) {
            return new Token(str, INTEGER);
        } else if (Token::is_float(str)) {
            return new Token(str, FLOAT);
        } else {
            return nullptr;
        }
    }

    // parses a given string as a string
    // @returns nullptr on failure, Token on success
    static Token* parse_string(string* str) {
        return new Token(str, STRING);
    }

    // tokenizes a given word
    // @returns nullptr on failure, otherwise an allocated Token
    static Token* tokenize(string* str) {
        // parse from most restrictive to least restrictive to minimize work
        if (str->size() == 0) {
            delete str;
            return new Token(nullptr, NONE);
        } else if (Token::is_bool(str)) {
            return new Token(str, BOOL);
        } else if (Token::is_integer(str) || Token::is_float(str)) {
            return Token::parse_number(str);
        } else if (Token::is_string(str)) {
            return Token::parse_string(str);
        } else {
            return nullptr;
        }
    }

    // 'tokenizes' or turns a line of input
    // into well-formed tokens
    // @returns nullptr on malformed
    static vector<Token*>* tokenize_line(string* line) {
        bool has_malformed_token = false;
        vector<Token*>* tokens = new vector<Token*>();
        for (size_t i = 0; i < line->length(); i++) {
            // find start delimiter '<', increment past
            if (line->at(i) != '<')
                continue;
            i++;

            // remove leading whitespace
            for (size_t j = i; j < line->length(); j++) {
                if (line->at(j) != ' ')
                    break;
                i++;
            }

            size_t start_index = i;

            // find end delimiter '>'
            size_t end_index;
            if (line->at(start_index) == '"') {
                // '>' within string quotes should be ignored
                size_t end_of_quote = Utility::str_next_index_of(line, start_index, '"');
                if (end_of_quote > line->size()) {
                    has_malformed_token = true;
                    break;
                }
                end_index = Utility::str_next_index_of(line, end_of_quote, '>');
            } else {
                end_index = Utility::str_next_index_of(line, start_index - 1, '>');
            }
            // increment i to end index
            i = end_index;
            
            if (end_index > line->size()) {
                has_malformed_token = true;
                break;
            }
            // decrement end index to one before delimiter
            end_index--;

            // remove trailing whitespace
            for (size_t j = end_index; j > start_index; j--) {
                if (line->at(j) != ' ')
                    break;
                end_index--;
            }

            // create substring 
            string* substring = Utility::substr(line, start_index, end_index + 1);

            // determine type
            Token* token = Token::tokenize(substring);
            if (!token) {
                has_malformed_token = true;
                delete substring;
                break;
            }
            tokens->push_back(token);
        }

        if (has_malformed_token) {
            for (size_t i = 0; i < tokens->size(); i++) {
                delete tokens->at(i);
            }
            tokens->clear();
            delete tokens;
            return nullptr;
        } else {
            return tokens;
        }
    }
};