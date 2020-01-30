#pragma once
#include "array.h"
#include "object.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Represents an array-structured list
 *
 */
class Bool_Array : public Array {
public:
  bool *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  Bool_Array() : Array() {
	  size_ = 0;
	  capacity_ = 4;
	  hash_code = 0;
    list = new bool[capacity_];
    hash();
  }

  // void initialize(size_t from) {
  // 	for (size_t i = from; i < capacity_; i++) {
  // 		list[i] = nullptr;
  // 	}
  // }

  void expand() {
    capacity_ *= 2;
    bool *temp = new bool[capacity_];
    for (size_t i = 0; i < size_; i++) {
      temp[i] = list[i];
    }
    delete[] list;
    list = temp;
    // initialize(size_);
  }

  /**
   * @brief pushes the given object onto array
   *
   * @param o the given object to be added
   */
  void append(bool i) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = i;
    size_++;
  }

  /**
   * @brief removes all elements from array
   *
   */
  void clear() {
    delete list;
    list = new bool[capacity_];
    size_ = 0;
  }

  /**
   * @brief checks if the given object is in array
   *
   * @param o object to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(bool i) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == i) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief duplicates array with all elements
   *
   * @return Array cloned array
   */
  // Bool_Array copy() {
  // 	Bool_Array *result = new Bool_Array();
  // 	result->size_ = size_;
  // 	result->capacity_ = capacity_;
  // 	result->list = list;
  // 	return result;
  // }

  /**
   * @brief retrieves the object at given position
   *
   * @param idx index position
   * @return Object object located at given index inside array
   */
  bool get(size_t idx) {
    assert(idx >= 0 && idx < size_);
    return list[idx];
  }

  /**
   * @brief adds the given object to array at given position
   *
   * @param o given object
   * @param idx index position
   */
  void insert(bool i, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = i;
      return;
    }
    bool *temp = new bool[capacity_];
    for (size_t j = 0; j < idx; j++) {
      temp[j] = list[j];
    }
    temp[idx] = i;
    for (size_t j = idx; j < size_; j++) {
      temp[j + 1] = list[j];
    }
    size_++;
    delete[] list;
    list = temp;
  }

  /**
   * @brief deletes the given object from array
   *
   * @param o object to be deleted
   * @return Object removed object, now unlinked from array
   */
  bool remove(size_t i) {
    assert(i < size_ && i >= 0);
    bool *temp = new bool[capacity_];
    bool cur;
    cur = temp[i];
    for (size_t j = 0; j < i; j++) {
      // puts(list[j]->getValue());
      temp[j] = list[j];
    }
    for (size_t j = i + 1; j < size_; j++) {
      // puts(list[j]->getValue());
      temp[j - 1] = list[j];
    }
    delete[] list;
    list = temp;
    size_--;
    return cur;
  }

  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += (list[i] + 17) * 13;
    }
  }

  size_t size() { return size_; }

  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }
};