#pragma once

#include <vector>
#include <string>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace std;


class Utility {
public:
    // Finds next occurence of given char, AFTER, given index
    // @returns val > length of string if not found, otherwise index of char
    static size_t str_next_index_of(string* str, size_t index, char c) {
        for (size_t i = index + 1; i < str->size(); i++) {
            if (str->at(i) == c)
                return i;
        }
        return str->size() + 1;
    }

    // Creates copy of substring
    // [start_index, end_index)
    static string* substr(string* str, size_t start_index, size_t end_index) {
        size_t total_length = (end_index - start_index) + 1;
        char* c_str = new char[total_length];
        str->copy(c_str, total_length - 1, start_index);
        c_str[total_length - 1] = '\0';
        string* substring = new string(c_str);
        delete[] c_str;
        return substring;
    }

    static void quit(const char* error_msg) {
        printf("%s\n", error_msg);
        exit(1);
    }

    static bool is_valid_uint(const char* str) {
        for (size_t i = 0; i < strlen(str); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    static size_t min(size_t a, size_t b) {
        return a < b ? a : b;
    }

    static size_t max(size_t a, size_t b) {
        return a > b ? a : b;
    }
};