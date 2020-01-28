#pragma once
#include <iostream>

class Object {
public:
  size_t hash_code;

  // constructor
  // hash code will be initilized to 0
  Object() {
    hash_code = 0;
    hash();
  }

  ~Object() {}

  // Check if this object is equal to given object.
  virtual bool equals(Object *object);

  // return field hash_code if hash code not equal to zero.
  // hash code won't be 0
  virtual size_t hash();

  // Make the hash code valid
  virtual void hash_me();
};