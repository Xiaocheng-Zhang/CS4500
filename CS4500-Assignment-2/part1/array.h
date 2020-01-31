#pragma once
#include "array.h"
#include "string.h"
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A default Object Array support user to read and write elements.
 * It allows Object type inputs. A String class is an Object, whcih
 * can be handle in this Array.
 */
class Array {
public:
  Object **list;
  size_t size_;
  size_t capacity_;
  size_t hash_code;

  /**
   * An Array constructor with initialized size, capacity, hashcode and
   * Object list.
   */
  Array() {
    size_ = 0;
    capacity_ = 4;
    list = new Object *[capacity_];
    initialize(0);
    hash_code = 0;
    hash();
  }

  /**
   * Deconstructor that free the memory automatically.
   */
  ~Array() { delete[] list; }

  virtual void initialize(size_t from) {
    for (size_t integer = from; integer < capacity_; integer++) {
      list[integer] = nullptr;
    }
  }

  /**
   * Expand the Object list if it is full.
   */
  void expand() {
    capacity_ *= 2;
    Object **temp = new Object *[capacity_];
    for (size_t i = 0; i < size_; i++) {
      temp[i] = list[i];
    }
    delete[] list;
    list = temp;
    initialize(size_);
  }

  /** Append the object to the rest of array.
   * @param object object is the object that needed to be put.
   */
  void append(Object *object) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = object;
    size_++;
  } // Appends object to end

  /**
   *  Add the object at index integer. Won't repace the element.
   * @param integer integer is the destination user want to add.
   * @param object object is the object that will be added.
   */
  void add(size_t integer, Object *object) {
    // will there be a space??
    assert(integer <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[integer]) {
      list[integer] = object;
      return;
    }
    Object **temp = new Object *[capacity_];
    for (size_t j = 0; j < integer; j++) {
      temp[j] = list[j];
    }
    temp[integer] = object;
    for (size_t j = integer; j < size_; j++) {
      temp[j + 1] = list[j];
    }
    size_++;
    delete[] list;
    list = temp;
  } // Inserts object at integer

  /**
   * clear the whole array elements.
  */
  void clear() {
    delete[] list;
    list = new Object *[capacity_];
    initialize(0);
    size_ = 0;
  }

  /**
   * check whether this array contains the input object.
   * @param object object is the object needed to be checked.
   * 
   * @return return true if it contains.
  */
  bool contains(Object *object) {
    Object *s = dynamic_cast<Object *>(object);
    if (!s) {
      return false;
    }
    for (size_t i = 0; i < size_; i++) {
      if (list[i]->equals(s)) {
        return true;
      }
    }
    return false;
  }

  /**
   * check two array equal or not.
   * use hashcode to check whether it is same or not.
   * @param object object is the array needed to be checked.
   * 
   * @return return whether two array are equal.
  */
  bool equals(Array *array) {
    if (size_ != array->size()) {
      return false;
    }
    if (hash() == array->hash()) {
      return true;
    }
    return false;
  } // Compares object with this list for equality.

  Object *get(size_t index) {
    assert(index < size_ && index >= 0);
    return list[index];
  } // Returns the element at index

  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  } // Returns the hash code value for this list.

  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += list[i]->hash();
      // list[integer]->print_hash();
    }
  }

  Object *remove(size_t integer) {
    assert(integer < size_ && integer >= 0);
    Object **temp = new Object *[capacity_];
    Object *cur;
    cur = temp[integer];
    for (size_t j = 0; j < integer; j++) {
      // puts(list[j]->getValue());
      temp[j] = list[j];
    }
    for (size_t j = integer + 1; j < size_; j++) {
      // puts(list[j]->getValue());
      temp[j - 1] = list[j];
    }
    delete[] list;
    list = temp;
    size_--;
    return cur;
  } // Removes the element at integer

  size_t size() { return size_; }
};

/**
 * @brief Represents an array-structured list
 *
 */
class Int_Array {
public:
  int *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  Int_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new int[capacity_];
    hash();
  }

  void expand() {
    capacity_ *= 2;
    int *temp = new int[capacity_];
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
   * @param object the given object to be added
   */
  void append(int integer) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = integer;
    size_++;
  }

  /**
   * @brief removes all elements from array
   *
   */
  void clear() {
    delete list;
    list = new int[capacity_];
    size_ = 0;
  }

  /**
   * @brief checks if the given int is in array
   *
   * @param integer integer to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(int integer) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == integer) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief retrieves the object at given position
   *
   * @param idx index position
   * @return Object object located at given index inside array
   */
  int get(size_t idx) {
    assert(idx >= 0 && idx < size_);
    return list[idx];
  }

  /**
   * @brief adds the given object to array at given position
   *
   * @param object given object
   * @param idx index position
   */
  void insert(int integer, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = integer;
      return;
    }
    int *temp = new int[capacity_];
    for (size_t j = 0; j < idx; j++) {
      temp[j] = list[j];
    }
    temp[idx] = integer;
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
   * @param object object to be deleted
   * @return Object removed object, now unlinked from array
   */
  int remove(size_t integer) {
    assert(integer < size_ && integer >= 0);
    int *temp = new int[capacity_];
    int cur;
    cur = temp[integer];
    for (size_t j = 0; j < integer; j++) {
      temp[j] = list[j];
    }
    for (size_t j = integer + 1; j < size_; j++) {
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

  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }

  size_t size() { return size_; }
};

/**
 * @brief Represents an array-structured list
 *
 */
class Bool_Array {
public:
  bool *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  Bool_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new bool[capacity_];
    hash();
  }

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
   * @param object the given object to be added
   */
  void append(bool integer) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = integer;
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
   * @param object object to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(bool integer) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == integer) {
        return true;
      }
    }
    return false;
  }

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
   * @param object given object
   * @param idx index position
   */
  void insert(bool integer, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = integer;
      return;
    }
    bool *temp = new bool[capacity_];
    for (size_t j = 0; j < idx; j++) {
      temp[j] = list[j];
    }
    temp[idx] = integer;
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
   * @param object object to be deleted
   * @return Object removed object, now unlinked from array
   */
  bool remove(size_t integer) {
    assert(integer < size_ && integer >= 0);
    bool *temp = new bool[capacity_];
    bool cur;
    cur = temp[integer];
    for (size_t j = 0; j < integer; j++) {
      // puts(list[j]->getValue());
      temp[j] = list[j];
    }
    for (size_t j = integer + 1; j < size_; j++) {
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

/**
 * @brief Represents an array-structured list
 *
 */
class Float_Array {
public:
  float *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  Float_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new float[capacity_];
    hash();
  }

  void expand() {
    capacity_ *= 2;
    float *temp = new float[capacity_];
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
   * @param object the given object to be added
   */
  void append(float integer) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = integer;
    size_++;
  }

  /**
   * @brief removes all elements from array
   *
   */
  void clear() {
    delete list;
    list = new float[capacity_];
    size_ = 0;
  }

  /**
   * @brief checks if the given object is in array
   *
   * @param object object to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(float integer) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == integer) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief retrieves the object at given position
   *
   * @param idx index position
   * @return Object object located at given index inside array
   */
  float get(size_t idx) {
    assert(idx >= 0 && idx < size_);
    return list[idx];
  }

  /**
   * @brief adds the given object to array at given position
   *
   * @param object given object
   * @param idx index position
   */
  void insert(float integer, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = integer;
      return;
    }
    float *temp = new float[capacity_];
    for (size_t j = 0; j < idx; j++) {
      temp[j] = list[j];
    }
    temp[idx] = integer;
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
   * @param object object to be deleted
   * @return Object removed object, now unlinked from array
   */
  float remove(size_t integer) {
    assert(integer < size_ && integer >= 0);
    float *temp = new float[capacity_];
    float cur;
    cur = temp[integer];
    for (size_t j = 0; j < integer; j++) {
      // puts(list[j]->getValue());
      temp[j] = list[j];
    }
    for (size_t j = integer + 1; j < size_; j++) {
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