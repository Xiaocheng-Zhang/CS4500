#pragma once
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "object.h"
#include "string.h"
#include "hashmap.h"
#include "integer.h"


int integer_cast(Object *object) {
    return dynamic_cast<Integer*>(object)->val_;
}

int char_filter (int c) {
    return !((0 < c && c < 48) || (57 < c && c < 65) ||
    (90 < c && c < 97) || 122 < c || c == -1);
}

void print_list(StrList *outputList, Hashmap *hashmap) {
    for (int i = 0; i < outputList->size(); i++) {
        int cur = integer_cast(hashmap->get(outputList->get(i)));
        printf("%s %d\n", outputList->get(i)->getValue(), cur);
    }
}

int buf_filter(char buf[]) {
    return strcmp(buf, "") != 0 && strlen(buf) > 4;
}

void save_data_to_sortedStrList(SortedStrList *sortedStrlist,
FILE *opened_file) {
    int c;
    int endf = 0;
    char buf[100];
    int size = 0;
    char *temp;
    Integer *integer;
    Object *object;
    while (endf != 1) {
        c = 0;
        size = 0;
        memset(buf, 0, sizeof(buf));
        //split: split with space bla bla bla
        while (char_filter(c) && endf != 1) {
            c = fgetc(opened_file);
            if (char_filter(c)) {
                c = tolower(c);
                buf[size] = (char) c;
                size++;
            }
            if (feof(opened_file)) {
                endf = 1;
            }
        }
        //end: split
        //filter: filter buf that does not need befor add to list.
        if (buf_filter(buf)) {
            temp = strdup(buf);
            String *s = new String(temp);
            sortedStrlist->sorted_add(s);
        }
        //end: filter
    }
}

void hashmap_pusher(Hashmap *hashmap, StrList *strList) {
    Integer *integer;
    String *cur;
    for (int i = 0; i < strList->size(); i++) {
        cur = strList->get(i);
        Object *object = hashmap->get(cur);
        integer = dynamic_cast<Integer*>(object);
        if (integer) {
            integer->val_++;
        }
        else {
            hashmap->put(cur, new Integer(1));
        }
    }
}


String** key_array_convert(Hashmap *hashmap) {
    String **output;
    output = new String*[hashmap->size()];
    Object **key_arr = hashmap->key_array();
    for (int i = 0; i < hashmap->size(); i++) {
        output[i] = dynamic_cast<String*>(key_arr[i]);
    }
    delete [] key_arr;
    return output;
}

int max_int(Hashmap *hashmap, String **keys) {
    int max = 0;
    //printf("%d", hashmap->size());
    for (int i = 0; i < hashmap->size(); i++) {
            int cur = integer_cast(hashmap->get(keys[i]));
        if (cur > max) {
            max = cur;
        }
    }
    return max;
}