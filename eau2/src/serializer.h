#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <type_traits>
#include <vector>

#include "dataframe.h"
#include "object.h"
#include "row.h"
#include "string.h"
#include "typedef.h"

using namespace std;

class Serializer : public Object {
private:
  vector<char *> data;

public:
  Serializer() {}

  char *serialize_int(int i) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, INTEGER);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", i);
    strcat(buffer, src);
    return buffer;
  }

  char *serialize_float(float f) {
    char *buffer = new char[32];
    sprintf(buffer, SERIALIZE_FORMAT, FLOAT);
    char *src = new char[sizeof(int)];
    sprintf(src, "%f\0", f);
    strcat(buffer, src);
    return buffer;
  }

  char *serialize_bool(bool b) {
    char *buffer = new char[2];
    sprintf(buffer, SERIALIZE_FORMAT, BOOL);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", b);
    strcat(buffer, src);
    return buffer;
  }

  char *serialize_double(double b) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, DOUBLE);
    char *src = new char[sizeof(int)];
    sprintf(src, "%lf\0", b);
    strcat(buffer, src);
    return buffer;
  }

  char *serialize_string(String *s) {
    char *buffer = new char[s->size() + 5];
    sprintf(buffer, SERIALIZE_FORMAT, STRING);
    strcat(buffer, s->cstr_);
    return buffer;
  }

  void serialize(DataFrame *element) {
    for (size_t i = 0; i < element->nrows(); i++) {
      Row* r = element->track_row(i);
      for (size_t j = 0; j < r->width(); j++) {
        if (r->col_type(j) == INTEGER_C) {
          data.push_back(serialize_int(r->get_int(j)));
        }
        else if (r->col_type(j) == FLOAT_C) {
          data.push_back(serialize_float(r->get_float(j)));
        }
        else if (r->col_type(j) == STRING_C) {
          data.push_back(serialize_string(r->get_string(j)));
        }
        else if (r->col_type(j) == BOOL_C) {
          data.push_back(serialize_bool(r->get_bool(j)));
        }
      }
    }
  }

  vector<char*> get_data() {
    return data;
  }
};