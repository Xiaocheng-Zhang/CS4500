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

  void initialize(size_t from) {
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
  }

  /**
   *  Add the object at index integer. Won't repace the element.
   * @param integer integer is the destination user want to add.
   * @param object object is the object that will be added.
   */
  void add(size_t integer, Object *object) {
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
  }

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
  }

  /**
   * get the element at given index
   * @param integer index is the position users want to get
   *
   * @return return the object at the given index.
   */
  Object *get(size_t index) {
    assert(index < size_ && index >= 0);
    return list[index];
  }

  /**
   * @return the hash code value of this array.
   */
  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }

  /**
   * @return helper funciton calculate the hash code
   */
  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += list[i]->hash();
      // list[integer]->print_hash();
    }
  }

  /**
   * remove the element at given index
   * @param integer index is the position users want to remove
   *
   * @return return the object removed at the given index.
   */
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
 * This array is designed only for int type. A user can read and
 * write int into this array
 */
class Int_Array {
public:
  int *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  /**
   * An Int Array constructor with initialized size, capacity, hashcode and
   * int list.
   */
  Int_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new int[capacity_];
    hash();
  }

  /**
   * Expand the int list if it is full.
   */
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
   * @return int int located at given index inside array
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
   * remove the element at given index
   * @param integer index is the position users want to remove
   *
   * @return return the int removed at the given index.
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

  /**
   * @return helper funciton calculate the hash code
   */
  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += (list[i] + 17) * 13;
    }
  }

  /**
   * @return the hash code value of this array.
   */
  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }

  size_t size() { return size_; }
};

/**
 * This array is designed only for bool type. A user can read and
 * write bool into this array
 */
class Bool_Array {
public:
  bool *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  /**
   * An Bool Array constructor with initialized size, capacity, hashcode
   * and bool list.
   */
  Bool_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new bool[capacity_];
    hash();
  }

  /**
   * Expand the bool list if it is full.
   */
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

  /** Append the bool to the rest of array.
   * @param bool bool is the element that needed to be put.
   */
  void append(bool b) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = b;
    size_++;
  }

  /**
   * clear the whole array elements.
   */
  void clear() {
    delete list;
    list = new bool[capacity_];
    size_ = 0;
  }

  /**
   * check whether this array contains the input bool.
   * @param bool bool is the element needed to be checked.
   *
   * @return return true if it contains.
   */
  bool contains(bool b) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == b) {
        return true;
      }
    }
    return false;
  }

  /**
   * get the element at given index
   * @param integer index is the position users want to get
   *
   * @return return the bool at the given index.
   */
  bool get(size_t idx) {
    assert(idx >= 0 && idx < size_);
    return list[idx];
  }

  /**
   * @brief adds the given bool to array at given position
   *
   * @param bool given bool
   * @param idx index position
   */
  void insert(bool b, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = b;
      return;
    }
    bool *temp = new bool[capacity_];
    for (size_t j = 0; j < idx; j++) {
      temp[j] = list[j];
    }
    temp[idx] = b;
    for (size_t j = idx; j < size_; j++) {
      temp[j + 1] = list[j];
    }
    size_++;
    delete[] list;
    list = temp;
  }

  /**
   * remove the element at given index
   * @param integer index is the position users want to remove
   *
   * @return return the bool removed at the given index.
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

  /**
   * @return helper funciton calculate the hash code
   */
  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += (list[i] + 17) * 13;
    }
  }

  /**
   * @return the size of this array.
   */
  size_t size() { return size_; }

  /**
   * @return the hash code value of this array.
   */
  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }
};

/**
 * This array is designed only for float type. A user can read and
 * write float into this array
 */
class Float_Array {
public:
  float *list;
  size_t capacity_;
  size_t size_;
  size_t hash_code;

  /**
   * An Float Array constructor with initialized size, capacity, hashcode
   * and float list.
   */
  Float_Array() {
    size_ = 0;
    capacity_ = 4;
    hash_code = 0;
    list = new float[capacity_];
    hash();
  }

  /**
   * Expand the float list if it is full.
   */
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

  /** Append the float to the rest of array.
   * @param float float is the object that needed to be put.
   */
  void append(float f) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = f;
    size_++;
  }

  /**
   * clear the whole array elements.
   */
  void clear() {
    delete list;
    list = new float[capacity_];
    size_ = 0;
  }

  /**
   * check whether this array contains the input float.
   * @param float float is the element needed to be checked.
   *
   * @return return true if it contains.
   */
  bool contains(float f) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == f) {
        return true;
      }
    }
    return false;
  }

  /**
   * get the element at given index
   * @param integer index is the position users want to get
   *
   * @return return the float at the given index.
   */
  float get(size_t idx) {
    assert(idx >= 0 && idx < size_);
    return list[idx];
  }

  /**
   * @brief adds the given float to array at given position
   *
   * @param float given float
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
   * remove the element at given index
   * @param integer index is the position users want to remove
   *
   * @return return the float removed at the given index.
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

  /**
   * @return helper funciton calculate the hash code
   */
  void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += (list[i] + 17) * 13;
    }
  }

  /**
   * @return the size of this array.
   */
  size_t size() { return size_; }

  /**
   * @return the hash code value of this array.
   */
  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }
};