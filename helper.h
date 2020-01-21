#include "object.h"
#include "string.h"
#include "list.h"
#include "hashmap.h"
#include "integer.h"
#include <stdio.h>


String* cast_string(Object* object) {
	return dynamic_cast<String*>(object);
}

Integer* cast_integer(Object* object) {
	return dynamic_cast<Integer*>(object);
}

void read_file(Hashmap *command_map, Hashmap *data_map) {
	String *file_path = cast_string(command_map->get(new String("-f")));
	Integer *from = cast_integer(command_map->get(new String("-from")));
	if (!from) {
		from = new Integer(0);
	}
	Integer *len = cast_integer(command_map->get(new String("-len")));
	if (!len) {
		len = new Integer(500);
	}

	FILE* fp;
	fp = fopen(file_path->getValue(),"r");
	fseek(fp, from->val_, SEEK_SET);
	size_t i = 0;
	int ic = 0;
	char c = 0;
	char prev = 0;
	char buffer[255];
	int buffer_index = 0;
	StrList *strl;
	int max_length = 0;
	int max_row = 0;
	//bool isRecording = false;
	size_t row = 0;
	bool p1 = true;
	bool p2 = true;
	//Read file from start to len. Store fields without empty space into a string list, then put into map.
	

	//all data
	while (i < len->val_) {
		strl = new StrList();
		//split single line
		while (c != '\n') {
			//split single field
			prev = 0;
			buffer_index = 0;
			memset(buffer, 0, sizeof(buffer));
		   	while (p1 || p2) {
		   		ic = fgetc(fp);
		   		c = (char) ic;
		   		if (c == '<') {
		   			p1 = false;
		   		}
		   		else if (c == '>') {
		   			p2 = false;
		   		}
		   		else if (prev == '>' && c == ' ') {
		   			buffer[buffer_index] = c;
		   			buffer_index++;
		   			prev = c;
		   		}
		   	}
		   	p1 = true;
		   	p2 = true;
		   	char* temp = strdup(buffer);
		   	strl->push_back(new String(temp));
		}
		if (strl->size() > max_length) {
			max_length = strl->size();
			max_row = row;
		}
		data_map->put(new Integer(row), strl);
		row++;
	}
}

