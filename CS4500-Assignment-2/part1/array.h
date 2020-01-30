#pragma once
#include "object.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Represents an array-structured list
 *
 */
class Array {
public:
  size_t size_;
  size_t capacity_;
  size_t hash_code;

  Array() {
	  size_ = 0;
	  capacity_ = 4;
	  hash_code = 0;
  }

  virtual void clear() {
	  size_ = 0;
  }

  virtual size_t size() { return size_; }

  virtual size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  } // Returns the hash code value for this list.

  virtual void hash_me() { hash_code = (size_t)this; }
};