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
    printf("Serialize: String %s to %s\n", s->c_str(), buffer);
    return buffer;
  };
  virtual char *serialize(int i) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, INTEGER);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", i);
    strcat(buffer, src);
    printf("Serialize: int %d to %s\n", i, buffer);
    return buffer;
  };
  virtual char *serialize(float f) {
    char *buffer = new char[32];
    sprintf(buffer, SERIALIZE_FORMAT, FLOAT);
    char *src = new char[sizeof(int)];
    sprintf(src, "%f\0", f);
    strcat(buffer, src);
    printf("Serialize: float %f to %s\n", f, buffer);
    return buffer;
  };
  virtual char *serialize(double f) {
    char *buffer = new char[64];
    sprintf(buffer, SERIALIZE_FORMAT, DOUBLE);
    char *src = new char[sizeof(int)];
    sprintf(src, "%lf\0", f);
    strcat(buffer, src);
    printf("Serialize: double %lf to %s\n", f, buffer);
    return buffer;
  };
  virtual char *serialize(bool b) {
    char *buffer = new char[2];
    sprintf(buffer, SERIALIZE_FORMAT, BOOL);
    char *src = new char[sizeof(int)];
    sprintf(src, "%d\0", b);
    strcat(buffer, src);
    printf("Serialize: bool %d to %s\n", b, buffer);
    return buffer;
  };
};

class AdvanceSerializer : public Serializer {
public:
  AdvanceSerializer() : Serializer() {}

  virtual char *serialize(StringArray *sa) { return nullptr; }
  virtual char *serialize(DoubleArray *da) { return nullptr; }
  virtual char *serialize(Message *msg) { return nullptr; }
  virtual char *serialize(Ack *ack) { return nullptr; }
  virtual char *serialize(Status *st) { return nullptr; }
  virtual char *serialize(Register *r) { return nullptr; }
  virtual char *serialize(Directory *d) { return nullptr; }
};
