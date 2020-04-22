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

class Deserializer : public Object {
public:

  Deserializer() : Object() {}

  DataFrame *deserialize(vector<char *> v) {
    Schema *schema = new Schema();
    // deserialize the width of dataframe
    char *buffer = new char[strlen(v[0]) - 5];
    for (size_t k = TYPE_OFFSET, j = 0; k < strlen(v[0]); k++) {
      buffer[j] = v[0][k];
      j++;
    }
    size_t size = atoi(buffer);

    // deserialize types and colnames
    for (size_t i = 1; i < size; i++) {
      char type = v[i][0];
      char col_name[strlen(v[i]) - 1];
      for (size_t k = 1, j = 0; k < strlen(v[i]); k++, j++) {
        col_name[j] = v[i][k];
      }
      if (strlen(col_name) != 0) {
        schema->add_column(type, new String(col_name));
      } else {
        schema->add_column(type, nullptr);
      }
    }
    // deserialize elements
    DataFrame *out = new DataFrame(*schema);
    for (size_t i = size, j = 0; i < v.size(); i++) {
      int type = atoi(v[i]);
      char *buffer = new char[strlen(v[i]) - 5];
      for (size_t k = TYPE_OFFSET, j = 0; k < strlen(v[i]); k++) {
        buffer[j] = v[i][k];
        j++;
      }
      Row *r = new Row(*schema);
      if (type == STRING) {
        r->set(j, new String(buffer));
      } else if (type == INTEGER) {
        r->set(j, atoi(buffer));
      } else if (type == DOUBLE) {
        r->set(j, (float) atof(buffer));
      } else if (type == BOOL) {
        r->set(j, atoi(buffer));
      }
      j++;
      if (j == size) {
        j = 0;
      }
    }
    return out;
  }
};