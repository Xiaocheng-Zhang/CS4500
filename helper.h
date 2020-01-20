#pragma once
#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include "cast_helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static String *f = new String("-f");
static String *from = new String("-from");
static String *len = new String("-len");
static String *print_col_type = new String("-print_col_type");
static String *print_col_idx = new String("-print_col_idx");
static String *is_missing_idx = new String("-is_missing_idx");

int array_contains(String **array, int size, String *val) {
    for (int i = 0; i < size; i++) {
        if (array[i] && array[i]->equals(val)) {
            return true;
        }
    }
    return false;
}

int multi_input_check(String *key) {
    if (key->equals(print_col_idx) || 
    key->equals(is_missing_idx)) {
        return true;
    }
    return false;
}

void set_keys(Hashmap *hashmap) {
    hashmap->put(f, nullptr);
    hashmap->put(from, nullptr);
    hashmap->put(len, nullptr);
    hashmap->put(print_col_type, nullptr);
    hashmap->put(print_col_idx, nullptr);
    hashmap->put(is_missing_idx, nullptr);
}

void read_command(Hashmap *hashmap, int argv, char** argc) {
    set_keys(hashmap);
    size_t size = hashmap->size();
    String** keys = cast_object_arr(hashmap->key_array(), size);
    //printf("%d\n", size);
    for (int i = 1; i < argv; i++) {
        String *key = new String(argc[i]);
        if (array_contains(keys, size, key)) {
            if (multi_input_check(key)) {
                StrList *strList = new StrList();
                i++;
                strList->push_back(new String(argc[i++]));
                strList->push_back(new String(argc[i]));
                hashmap->put(key, strList);
            }
            else {
                hashmap->put(key, new String(argc[i+1]));
                i++;
            }
            
        }
    }
}

void hashmap_print(Hashmap *hashmap) {
    size_t size = hashmap->size();
    String **print_list = cast_object_arr(hashmap->key_array(), size);
    for (int i = 0; i < size; i++) {
        String *cur = print_list[i];
        String *val = cast_string(hashmap->get(cur));
        if (val) {
            printf("key: %s val: %s\n", cur->getValue(), val->getValue());
        }
        StrList *list = cast_list(hashmap->get(cur));
        if (list) {
            //printf("key: %s val: %s %s\n", cur->getValue(), 
            //list->get(0)->getValue(), list->get(1)->getValue());
        }
    }
}