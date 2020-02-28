#pragma once
#include <stdlib.h>
#include <string.h>

//#include "object.h"
#include "string.h"
#include "serial.h"
#include "types.h"
//#include "vec.h"

class Serializer {
public:
  Serializer() {}
  virtual char *serialize(String *s) {
    // "0 test1"
    char *buffer = new char[s->size() + 5];
    sprintf(buffer, SERIALIZE_FORMAT, STRING);
    strcat(buffer, s->cstr_);
    return buffer;
  };
  virtual char *serialize(int i) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, INTEGER);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", i);
    strcat(buffer, src);
    return buffer;
  };
  virtual char *serialize(float f) {
    char *buffer = new char[32];
    sprintf(buffer, SERIALIZE_FORMAT, FLOAT);
    char *src = new char[sizeof(int)];
    sprintf(src, "%f\0", f);
    strcat(buffer, src);
    return buffer;
  };
  virtual char *serialize(double f) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, DOUBLE);
    char *src = new char[sizeof(int)];
    sprintf(src, "%lf\0", f);
    strcat(buffer, src);
    return buffer;
  };
  virtual char *serialize(bool b) {
    char *buffer = new char[2];
    sprintf(buffer, SERIALIZE_FORMAT, BOOL);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", b);
    strcat(buffer, src);
    return buffer;
  };
};

class AdvanceSerializer : public Serializer {
public:
  AdvanceSerializer() : Serializer() {}
  
  virtual char *serialize(StringArray *sa) {
    // char *buffer = new char[sa->size_];
    return nullptr;
  }
};
