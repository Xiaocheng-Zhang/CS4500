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

  void serialize(DataFrame* element) {
    char buf[1024];
      for (size_t i = 0; i < element->nrows(); i++) {
        
      }
  }
};

class Deserializer : public Object {};
