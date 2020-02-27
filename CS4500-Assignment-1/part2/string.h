#pragma once

#include "object.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A String is an Object
class String : public Object {
public:
  const char *value_;
  int size_;
  size_t hash_code;

  // Constructor
  // hash code will be initialized to 0
  // the given char* will be contrcted into String
  String(const char *value) : Object() {
    value_ = value;
    size_ = strlen(value);
    hash_code = 0;
    hash();
  }
  ~String() { delete[] value_; }

  // Return the size of the String
  virtual size_t get_size();

  // Check if this String is equal to given String.
  // Gievn String is an object
  virtual bool equals(Object *object);

  // Concatinate given String to this String.
  // This String will be in the front
  String *concat(String *o);

  // Return field hash_code if hash code is not zero.
  // Otherwise go to hash_me function.
  virtual size_t hash();

  // Make hash code a valid hash code
  virtual void hash_me();

  // Return char pointer value_
  virtual const char *getValue();
};