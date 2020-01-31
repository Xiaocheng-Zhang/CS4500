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
    for (size_t i = from; i < capacity_; i++) {
      list[i] = nullptr;
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
   * @param e e is the object that needed to be put.
   */
  void append(Object *e) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = e;
    size_++;
  } // Appends e to end

  /**
   *  Add the object at index i. Won't repace the element.
   * @param i i is the destination user want to add.
   * @param e e is the object that will be added.
   */
  void add(size_t i, Object *e) {
    // will there be a space??
    assert(i <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[i]) {
      list[i] = e;
      return;
    }
    Object **temp = new Object *[capacity_];
    for (size_t j = 0; j < i; j++) {
      temp[j] = list[j];
    }
    temp[i] = e;
    for (size_t j = i; j < size_; j++) {
      temp[j + 1] = list[j];
    }
    size_++;
    delete[] list;
    list = temp;
  } // Inserts e at i

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
   * @param o o is the object needed to be checked.
   * 
   * @return return true if it contains.
  */
  bool contains(Object *o) {
    Object *s = dynamic_cast<Object *>(o);
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
   * @param o o is the array needed to be checked.
   * 
   * @return return whether two array are equal.
  */
  bool equals(Array *o) {
    if (size_ != o->size()) {
      return false;
    }
    if (hash() == o->hash()) {
      return true;
    }
    return false;
  } // Compares o with this list for equality.

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
      // list[i]->print_hash();
    }
  }

  Object *remove(size_t i) {
    assert(i < size_ && i >= 0);
    Object **temp = new Object *[capacity_];
    Object *cur;
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
  } // Removes the element at i

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
   * @param o the given object to be added
   */
  void append(int i) {
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
    list = new int[capacity_];
    size_ = 0;
  }

  /**
   * @brief checks if the given object is in array
   *
   * @param o object to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(int i) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == i) {
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
   * @param o given object
   * @param idx index position
   */
  void insert(int i, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = i;
      return;
    }
    int *temp = new int[capacity_];
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
  int remove(size_t i) {
    assert(i < size_ && i >= 0);
    int *temp = new int[capacity_];
    int cur;
    cur = temp[i];
    for (size_t j = 0; j < i; j++) {
      temp[j] = list[j];
    }
    for (size_t j = i + 1; j < size_; j++) {
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
   * @param o the given object to be added
   */
  void append(float i) {
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
    list = new float[capacity_];
    size_ = 0;
  }

  /**
   * @brief checks if the given object is in array
   *
   * @param o object to be checked
   * @return true if object in array
   * @return false if object not in array
   */
  bool contains(float i) {
    for (size_t m = 0; m < size_; m++) {
      if (list[m] == i) {
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
   * @param o given object
   * @param idx index position
   */
  void insert(float i, size_t idx) {
    assert(idx >= 0 && idx <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[idx]) {
      list[idx] = i;
      return;
    }
    float *temp = new float[capacity_];
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
  float remove(size_t i) {
    assert(i < size_ && i >= 0);
    float *temp = new float[capacity_];
    float cur;
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