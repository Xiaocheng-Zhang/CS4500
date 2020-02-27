#pragma once
#include "object.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

// Hashmap_pair is a node, which is used to to store a pair of key and value.
// Later a list of Hashmap_pair will be stored into Hashmap data structure.
// It inherit Object class.
class Hashmap_pair : public Object {
public:
  Object *key_;
  Object *val_;
  Hashmap_pair(Object *key, Object *val) : Object() {
    key_ = key;
    val_ = val;
  }
  ~Hashmap_pair() {
    delete key_;
    delete val_;
  }
};

// Hashmap class stores a list of hashmap_pairs, which contains equal number
// of keys and values.
// It has size and capcity, which size is the number of key-value pairs,
// and capcity is the physical size of hashmap.
class Hashmap : public Object {
public:
  Hashmap_pair **data;
  size_t size_;
  size_t capacity_;
  // constructor
  // capcity will be initilized as 4, size is 0 by default.
  Hashmap() {
    data = new Hashmap_pair *[4];
    size_ = 0;
    capacity_ = 4;
  }

  // destructor
  ~Hashmap() { delete[] data; }

  // Double the capacity of hashmap when needed
  void expand();

  // Returns the value to which the specified key is mapped,
  // or null if this map contains no mapping for the key.
  Object *get(Object *key);

  // Associates the specified value with the specified key in this map.
  void put(Object *key, Object *val);

  // Removes the mapping for the specified key from this map if present.
  void remove(Object *key);

  // Returns the number of key-value mappings in this map.
  size_t size();

  // Returns a list view of the keys contained in this map.
  Object **key_array();

  // Check if two Hashmaps are equal.
  // the input hashmap is an object.
  bool equals(Object *map);
};
