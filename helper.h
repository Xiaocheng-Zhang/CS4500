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

int array_contains(String **array, int size, String *val) {
    for (int i = 0; i < size; i++) {
        if (array[i] && array[i]->equals(val)) {
            return true;
        }
    }
    return false;
}

void set_keys(Hashmap *hashmap) {
    hashmap->put(new String("-f"), nullptr);
    hashmap->put(new String("-from"), nullptr);
    hashmap->put(new String("-len"), nullptr);
    hashmap->put(new String("-print_col_type"), nullptr);
    hashmap->put(new String("-print_col_idx"), nullptr);
    hashmap->put(new String("-is_missing_idx"), nullptr);
}

void read_command(Hashmap *hashmap, int argv, char** argc) {
    set_keys(hashmap);
    size_t size = hashmap->size();
    String** keys = cast_object_arr(hashmap->key_array(), size);
    //printf("%d\n", size);
    for (int i = 1; i < argv; i++) {
        if (array_contains(keys, size, new String(argc[i]))) {
            hashmap->put(new String(argc[i]), new String(argc[i+1]));
            i++;
        }
    }
}

void hashmap_print(Hashmap *hashmap) {
    size_t size = hashmap->size();
    String **print_list = cast_object_arr(hashmap->key_array(), size);
    //printf("%d", size);
    for (int i = 0; i < size; i++) {
        String *cur = print_list[i];
        String *val = cast_string(hashmap->get(cur));
        if (val) {
        printf("key: %s val: %s\n", cur->getValue(), val->getValue());
        }
    }
}