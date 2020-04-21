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
  DataFrame *deserialize(vector<char *> v) {
    Schema *schema = new Schema();
    DataFrame *output = new DataFrame(*schema);
    for (size_t i = 0; i < v.size(); i++) {
      int type = atoi(v[i]);
      char *buffer = new char[strlen(v[i]) - 5];
      for (size_t j = TYPE_OFFSET, j = 0; j < strlen(v[i]); j++) {
        buffer[j] = v[i][j];
        j++;
      }
      if (type == STRING) {
        //output->add_column(, nullptr);
      }
      if (type == INTEGER) {
        // schema->add_column('I', nullptr);
        // int i = atoi(buffer);
        // void *out = &i;
        // return out;
      }
      if (type == DOUBLE) {
        // schema->add_column('D', nullptr);
        // float f = atof(buffer);
        // void *out = &f;
        // return out;
      }
      if (type == FLOAT) {
        // schema->add_column('F', nullptr);
        // float f = atof(buffer);
        // void *out = &f;
        // return out;
      }
      if (type == BOOL) {
        // schema->add_column('B', nullptr);
        // bool b = atoi(buffer);
        // void *out = &b;
        // return out;
      }
    }
  }
};