#pragma once
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "string.h"

class vec : public Object {
public:
  virtual void append(char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(char c)"
              << std::endl;
  }
  virtual void append(String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(String *s)"
              << std::endl;
  }
  virtual void set(size_t idx, char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, char c)"
              << std::endl;
  }
  virtual void set(size_t idx, String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, String *s)"
              << std::endl;
  }
  virtual void insert(size_t idx, char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, char c)"
              << std::endl;
  }
  virtual void insert(size_t idx, String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, String* s)"
              << std::endl;
  }
  virtual void print_self() {
    puts(
        "invalid function call in vec.h: vec is an abstract class: print_self");
  }
};

class cvec : public vec {
public:
  char *list_;
  size_t size_;
  size_t capacity_;
  size_t hash_;

  cvec(char c...) {}

  cvec() {
    size_ = 0;
    capacity_ = 4;
    hash_ = 0;
    list_ = new char[capacity_];
  }

  ~cvec() { delete[] list_; }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      char *temp = new char[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
    }
    assert(size_ < capacity_);
  }

  virtual void append(char c) {
    expand();
    list_[size_] = c;
    size_++;
  }

  virtual void set(size_t idx, char c) {
    expand();
    list_[idx] = c;
  }

  virtual void insert(size_t idx, char c) {
    expand();
    char *temp = new char[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = c;
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }

  /**
   * overrite hash_me to hash the code.
   * @return return hash code.
   */
  virtual size_t hash_me() {
    for (size_t i = 0; i < size_; i++) {
      hash_ = hash_ * 67 + list_[i] * 13;
    }
    return hash_;
  }

  virtual void print_self() {
    for (size_t i = 0; i < size_; i++) {
      printf("%c", list_[i]);
    }
  }
};

class svec : public vec {
public:
  String **list_;
  size_t size_;
  size_t capacity_;
  size_t hash_;

  svec(String *s...) {}

  svec() {
    size_ = 0;
    capacity_ = 4;
    hash_ = 0;
    list_ = new String *[capacity_];
    initialize(0);
  }

  ~svec() { delete[] list_; }

  void initialize(size_t idx) {
    for (size_t i = idx; i < capacity_; i++) {
      list_[i] = nullptr;
    }
  }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      String **temp = new String *[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
      initialize(size_);
    }
    assert(size_ < capacity_);
  }

  virtual void append(String *s) {
    expand();
    list_[size_] = s;
    size_++;
  }

  virtual void set(size_t idx, String *s) {
    expand();
    list_[idx] = s;
  }

  virtual void insert(size_t idx, String *s) {
    expand();
    String **temp = new String *[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = s;
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }

  /**
   * overrite hash_me to hash the code.
   * @return return hash code.
   */
  virtual size_t hash_me() {
    for (size_t i = 0; i < size_; i++) {
      hash_ = hash_ * 67 + list_[i]->hash() * 13;
    }
    return hash_;
  }

  virtual void print_self() {
    for (size_t i = 0; i < size_; i++) {
      if (list_[i]) {
        printf("%s ", list_[i]->c_str());
      }
    }
  }
};