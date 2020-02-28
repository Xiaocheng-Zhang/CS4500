#pragma once
#include <stdlib.h>
#include <string.h>

//#include "object.h"
#include "string.h"
#include "vec.h"

class Keeper {
public:
  Svec *serialized_buffer_list;
  virtual ~Keeper() { delete serialized_buffer_list; }
  // each element in the list represent a full type
  virtual void write_file(char *filename) {
    FILE *fd = fopen(filename, "a+");
    size_t size = serialized_buffer_list->size();
    for (size_t i = 0; i < size; i++) {
      char *temp = serialized_buffer_list->get_String(i)->cstr_;
      char *s = new char[strlen(temp) + 1];
      strcpy(s, temp);
      s[strlen(temp)] = '\n'; // add '\n' at the end
      fwrite(s, sizeof(char), strlen(s), fd);
    }
  }

  // append serialized data to the list
  virtual void append(char *s) {
    serialized_buffer_list->append(new String(s));
  }

  // append serialized data to the list
  virtual void append(String *s) { serialized_buffer_list->append(s); }
};

class BasicKeeper : public Keeper {
public:
  BasicKeeper(Svec *vec) : Keeper() { serialized_buffer_list = vec; }
  BasicKeeper() : Keeper() { serialized_buffer_list = new Svec(); }
  ~BasicKeeper() {}
};