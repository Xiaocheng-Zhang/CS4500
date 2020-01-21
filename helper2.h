#pragma once
#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include "cast_helper.h"
#include "helper1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int loop_read(FILE *opened_f, Integer *len, Hashmap *data_map) {
    size_t i = 0;
	int ic = 0;
	char c = 0;
	char prev = 0;
	char buffer[255];
	int buffer_index = 0;
	StrList *strl = new StrList();
	int max_length = 0;
	int max_row = 0;
	size_t row = 0;
	bool p1 = true;
	bool p2 = true;
	//Read file from start to len. Store fields without empty
    //space into a string list, then put into map.
	bool end_of_f = false;
	//all data_map
	//split single line
    //printf("%d\n", len->val_);
	while (i < len->val_ && !end_of_f)
    {
        buffer_index = 0;
        memset(buffer, 0, sizeof(buffer));
        while ((p1 || p2) && i < len->val_)
        {
            ic = fgetc(opened_f);
            c = (char) ic;
            if (c == '<') {
                p1 = false;
            }
            if (c == '>') {
                p2 = false;
            }
            if (prev == '>' && c == ' ') {
                i++;
                continue;
            }
            if (c == '\n') {
                prev = 0;
                i++;
                break;
            }
            if (feof(opened_f)) {
                end_of_f = true;
                break;
            }
            buffer[buffer_index] = c;
            buffer_index++;
            prev = c;
            i++;
        }
        //push String to list
        //reset p1 p2
        p1 = true;
        p2 = true;
        char* temp = strdup(buffer);
        strl->push_back(new String(temp));
        //change line
        if (c == '\n' || end_of_f || i == len->val_) {
            if (strl->size() > max_length) {
                max_row = row;
                max_length = strl->size();
            }
            data_map->put(new Integer(row), strl);
            strl = new StrList();
            row++;
        }
    }
    return max_row;
}