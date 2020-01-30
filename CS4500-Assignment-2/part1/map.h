#pragma once
#include "node.h"
#include "object.h"
#include <assert.h>

class Map {
public:
  // Size of the current map
  size_t len_;
  size_t capacity_;
  // Array of Node pointers in the map
  Node **elems_;

  // Constructor
  Map() {
    elems_ = NULL;
    capacity_ = 10;
    len_ = 0;
    elems_ = new Node *[capacity_];
    initialize(elems_);
  }

  ~Map() { delete[] elems_; }

  /** initialize the map*/
  void initialize(Node **temp) {
    for (int i = 0; i < capacity_; i++) {
      temp[i] = nullptr;
    }
  }

  /** hash the index of keys*/
  size_t hash_index(Object *key) {
    if (key) {
      return key->hash() & (capacity_ - 1);
    }
    return -1;
  }

  /** helper method to increase the index i in hash_put method*/
  size_t index_grow(size_t i) {
    if (i == capacity_ - 1) {
      return 0;
    }
    return i + 1;
  }

  /** check whether the loop needs end in hash_put method*/
  bool index_check(size_t i, size_t index, size_t count) {
    if (i == index && count != 0) {
      return false;
    }
    return true;
  }

  /** return all keys as one array*/
  Object **key_array() {
    Object **keys = new Object *[len_];
    for (size_t i = 0, j = 0; i < capacity_; i++) {
      assert(j <= len_);
      if (elems_[i]) {
        keys[j] = elems_[i]->getKey();
        j++;
      }
    }
    return keys;
  }

  /** put key and val into temp_map*/
  void hash_put(Node **temp_elems, Object *key, Object *val) {
    size_t index = hash_index(key);
    assert(index != -1);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      if (!temp_elems[i]) {
        temp_elems[i] = new Node(key, val);
        len_++;
        return;
      } else if (temp_elems[i]->key_->equals(key)) {
        temp_elems[i]->value_ = val;
        return;
      }
    }
  }

  /** expand the node array size*/
  void expand() {
    capacity_ *= 2;
    size_t prev_len_ = len_;
    len_ = 0;
    Node **new_elems = new Node *[capacity_];
    initialize(new_elems);
    for (size_t i = 0, count = 0; count < prev_len_ && i < capacity_ / 2; i++) {
      if (elems_[i]) {
        hash_put(new_elems, elems_[i]->key_, elems_[i]->value_);
        count++;
      }
    }
    delete[] elems_;
    elems_ = new_elems;
  }

  // Adds an element to the map as a node pair
  void addElement(Object *key, Object *value) {
    if (len_ == capacity_) {
      expand();
    }
    hash_put(elems_, key, value);
  }

  // Removed the given key from the map
  void removeElement(Object *key) {
    size_t index = hash_index(key);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      if (elems_[i]) {
        if (elems_[i]->key_->equals(key)) {
          elems_[i] = nullptr;
          len_--;
        }
      }
    }
  }

  // Gets the value of the key
  Object* getValue(Object *key) {
    size_t index = hash_index(key);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      Node *cur = elems_[i];
      if (cur) {
        if (cur->key_->equals(key)) {
          return cur->value_;
        }
      }
    }
    return nullptr;
  }

  // Gets the length of the map
  size_t getLength() { return len_; }

  // Checks is the key is in the map
  bool isKeyIn(Object *e) {
    for (size_t i = 0; i < capacity_; i++) {
      if (elems_[i] && elems_[i]->key_->equals(e)) {
        return true;
      }
    }
    return false;
  }

  /** check does elems_ contains this node*/
  bool contains(Node *node) {
    for (size_t i = 0, j = 0; j < len_ && i < capacity_; i++) {
      if (elems_[i]) {
        j++;
        if (elems_[i]->equals(node)) {
          return true;
        }
      }
    }
    return false;
  }

  /** check whether two maps are equal*/
  bool equals(Map *map) {
    if (map->len_ == len_) {
      for (size_t i = 0; i < map->capacity_; i++) {
        Node *cur = map->elems_[i];
        if (cur) {
          if (!contains(cur)) {
            return false;
          }
        }
      }
      return true;
    }

    return false;
  }
};
