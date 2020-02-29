#pragma once
#include <stdlib.h>
#include <string.h>

//#include "object.h"
#include "serial.h"
#include "string.h"
#include "types.h"

void *basic_deserialize(int type, String *s) {
  char *temp = strdup(s->cstr_);
  char *buffer = new char[s->size() - 5];
  for (size_t i = TYPE_OFFSET, j = 0; i < s->size(); i++) {
    buffer[j] = temp[i];
    j++;
  }
  if (type == STRING) {
    return new String(buffer);
  }
  if (type == INTEGER) {
    int i = atoi(buffer);
    void *out = &i;
    return out;
  }
  if (type == DOUBLE) {
    float f = atof(buffer);
    void *out = &f;
    return out;
  }
  if (type == FLOAT) {
    float f = atof(buffer);
    void *out = &f;
    return out;
  }
  if (type == BOOL) {
    bool b = atoi(buffer);
    void *out = &b;
    return out;
  }
  return nullptr;
}

// void *class_deserialize(int type, StringArray *sa) {}

class Deserializer {
public:
  Deserializer() {}

  virtual void deserialize(String *sa) {
    int type = atoi(sa->c_str());
    void *output = basic_deserialize(type, sa);
    if (type == STRING) {
      printf("Deserialized: STRING %s", ((String *)output)->c_str());
    }
    if (type == INTEGER) {
      printf("Deserialized: INTEGER %d\n", *((int *)output));
    }
    if (type == FLOAT) {
      printf("Deserialized: FLOAT %f\n", *((float *)output));
    }
    if (type == DOUBLE) {
      printf("Deserialized: DOUBLE %lf\n", *((double *)output));
    }
    if (type == BOOL) {
      printf("Deserialized: BOOL %d\n", *((bool *)output));
    }
  }

  virtual void deserialize(StringArray *sa) {}

  virtual void *read_data(char *filename) {
    FILE *fd = fopen(filename, "r");
    char buf[1024];
    StringArray *sa = new StringArray();
    while (1) {
      char *input = fgets(buf, 1024, fd);
      fflush(stdout);
      if (!input) {
        break;
      }
      // found a class type sent.
      // found a basic type sent.
      deserialize(new String(input));
    }
    return nullptr;
  }
};

// class AdvanceDeserializer : public Deserializer {
// public:
//   AdvanceDeserializer() : Deserializer() {}

//   virtual char *serialize(StringArray *sa) {
//     // char *buffer = new char[sa->size_];
//   }
// };
