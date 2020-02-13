#pragma once
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "string.h"
#include "column.h"

class Vec : public Object {
public:
  size_t size_;
  size_t capacity_;
  size_t hash_;
  Vec() {
    size_ = 0;
    capacity_ = 4;
    hash_ = 0;
  }
  virtual void append(char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(char c)"
              << std::endl;
  }
  virtual void append(float f) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(float f)"
              << std::endl;
  }
  virtual void append(int i) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(int i)"
              << std::endl;
  }
  virtual void append(String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(String *s)"
              << std::endl;
  }
  virtual void append(Vec *v) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: append(Vec *v)"
              << std::endl;
  }
  virtual void set(size_t idx, char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, char c)"
              << std::endl;
  }
  virtual void set(size_t idx, float f) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, float f)"
              << std::endl;
  }
  virtual void set(size_t idx, int i) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, int i)"
              << std::endl;
  }
  virtual void set(size_t idx, String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, String *s)"
              << std::endl;
  }
  virtual void set(size_t idx, Vec *v) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: set(size_t idx, Vec *v)"
              << std::endl;
  }
  virtual void insert(size_t idx, char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, char c)"
              << std::endl;
  }
  virtual void insert(size_t idx, float f) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, float f)"
              << std::endl;
  }
  virtual void insert(size_t idx, int i) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, int i)"
              << std::endl;
  }
  virtual void insert(size_t idx, String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, String *s)"
              << std::endl;
  }
  virtual void insert(size_t idx, Vec *v) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: insert(size_t idx, Vec *v)"
              << std::endl;
  }
  virtual bool contains(char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: contains(char c)"
              << std::endl;
    return false;
  }
  virtual bool contains(float f) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: contains(float f)"
              << std::endl;
    return false;
  }
  virtual bool contains(int i) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: contains(int i)"
              << std::endl;
    return false;
  }
  virtual bool contains(String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: contains(String *s)"
              << std::endl;
    return false;
  }
  virtual bool contains(Vec *v) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: contains(Vec *v)"
              << std::endl;
    return false;
  }
  virtual int indexAt(char c) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: indexAt(char c)"
              << std::endl;
    return -1;
  }
  virtual int indexAt(float f) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: indexAt(float f)"
              << std::endl;
    return -1;
  }
  virtual int indexAt(int i) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: indexAt(int i)"
              << std::endl;
    return -1;
  }
  virtual int indexAt(String *s) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: indexAt(String *s)"
              << std::endl;
    return -1;
  }
  virtual int indexAt(Vec *v) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: indexAt(Vec *v)"
              << std::endl;
    return -1;
  }
  virtual void del(size_t idx) {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: del(size_t idx)"
              << std::endl;
  }
  virtual Vec *copy() {
    std::cout << "invalid function call in vec.h: vec is an abstract class\n"
                 "crashed method: copy()"
              << std::endl;
    return nullptr;
  }
  virtual size_t size() { return size_; }
  virtual void print_self() {
    puts(
        "invalid function call in vec.h: vec is an abstract class: print_self");
  }
};

class Cvec : public Vec {
public:
  char *list_;

  Cvec() : Vec() {
    list_ = new char[capacity_];
  }

  ~Cvec() { delete[] list_; }

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

  virtual bool contains(char c) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == c) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(char c) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == c) {
        return m;
      }
    }
    return -1;
  }

  virtual void del(size_t idx) {
    char *temp = new char[capacity_];
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i > j) {
        temp[j] = list_[i];
        j++;
      }
    }
    size_--;
    delete[] list_;
    list_ = temp;
  }

  virtual Vec *copy() {
    Vec *temp = new Cvec();
    for (size_t i = 0; i < size_; i++) {
      temp->append(list_[i]);
    }
    return temp;
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

class Fvec : public Vec {
public:
  float *list_;

  Fvec() : Vec() { list_ = new float[capacity_]; }

  ~Fvec() { delete[] list_; }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      float *temp = new float[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
    }
    assert(size_ < capacity_);
  }

  virtual void append(float f) {
    expand();
    list_[size_] = f;
    size_++;
  }

  virtual void set(size_t idx, float f) {
    expand();
    list_[idx] = f;
  }

  virtual void insert(size_t idx, float f) {
    expand();
    float *temp = new float[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = f;
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }

  virtual bool contains(float f) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == f) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(float f) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == f) {
        return m;
      }
    }
    return -1;
  }

  virtual void del(size_t idx) {
    float *temp = new float[capacity_];
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i > j) {
        temp[j] = list_[i];
        j++;
      }
    }
    size_--;
    delete[] list_;
    list_ = temp;
  }

  virtual Vec *copy() {
    Vec *temp = new Fvec();
    for (size_t i = 0; i < size_; i++) {
      temp->append(list_[i]);
    }
    return temp;
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
      printf("%f", list_[i]);
    }
  }
};

class Ivec : public Vec {
public:
  int *list_;

  Ivec() : Vec() { list_ = new int[capacity_]; }

  ~Ivec() { delete[] list_; }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      int *temp = new int[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
    }
    assert(size_ < capacity_);
  }

  virtual void append(int i) {
    expand();
    list_[size_] = i;
    size_++;
  }

  virtual void set(size_t idx, int i) {
    expand();
    list_[idx] = i;
  }

  virtual void insert(size_t idx, int integer) {
    expand();
    int *temp = new int[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = integer;
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }

  virtual bool contains(int i) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == i) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(int i) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == i) {
        return m;
      }
    }
    return -1;
  }

  virtual void del(size_t idx) {
    int *temp = new int[capacity_];
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i > j) {
        temp[j] = list_[i];
        j++;
      }
    }
    size_--;
    delete[] list_;
    list_ = temp;
  }

  virtual Vec *copy() {
    Vec *temp = new Ivec();
    for (size_t i = 0; i < size_; i++) {
      temp->append(list_[i]);
    }
    return temp;
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
      printf("%d", list_[i]);
    }
  }
};

class Svec : public Vec {
public:
  String **list_;

  Svec(String *s...) : Vec() {}

  Svec() : Vec() {
    list_ = new String *[capacity_];
    initialize(0);
  }

  ~Svec() { delete[] list_; }

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
    list_[size_] = new String(*s);
    size_++;
  }

  virtual void set(size_t idx, String *s) {
    expand();
    list_[idx] = new String(*s);
  }

  virtual void insert(size_t idx, String *s) {
    expand();
    String **temp = new String *[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = new String(*s);
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }
  virtual bool contains(String *s) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == s) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(String *s) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == s) {
        return m;
      }
    }
    return -1;
  }
  virtual void del(size_t idx) {
    String **temp = new String *[capacity_];
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i > j) {
        temp[j] = list_[i];
        j++;
      }
    }
    size_--;
    delete[] list_;
    list_ = temp;
  }
  virtual Vec *copy() {
    Vec *temp = new Svec();
    for (size_t i = 0; i < size_; i++) {
      temp->append(list_[i]);
    }
    return temp;
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

class ColumnVec : public Vec {
public:
  Column **list_;

  ColumnVec() : Vec() {
    list_ = new Column *[capacity_];
    initialize(0);
  }

  ~ColumnVec() {
    delete [] list_;
  }

  void initialize(size_t idx) {
    for (size_t i = idx; i < capacity_; i++) {
      list_[i] = nullptr;
    }
  }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      Column **temp = new Column *[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
      initialize(size_);
    }
    assert(size_ < capacity_);
  }

  virtual void append(Column *v) {
    expand();
    Column *temp = v;//v->copy();
    list_[size_] = temp;
    // memcpy(list_[size_], v, sizeof(v));
    size_++;
  }

  virtual void set(size_t idx, Column *v) {
    expand();
    list_[idx] = v;//v->copy();
  }

  virtual void insert(size_t idx, Column *v) {
    expand();
    Column **temp = new Column *[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = v;//v->copy();
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }
  virtual bool contains(Column *v) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m]->equals(v)) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(Column *v) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m]->equals(v)) {
        return m;
      }
    }
    return -1;
  }
  virtual void del(size_t idx) {
    Column **temp = new Column *[capacity_];
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i > j) {
        temp[j] = list_[i];
        j++;
      }
    }
    size_--;
    delete[] list_;
    list_ = temp;
  }
  virtual Vec *copy() {
    Vec *temp = new ColumnVec();
    for (size_t i = 0; i < size_; i++) {
      //temp->append(list_[i]);
    }
    return temp;
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

  // virtual void print_self() {
  //   for (size_t i = 0; i < size_; i++) {
  //     if (list_[i]) {
  //       list_[i]->print_self();
  //       puts("");
  //     }
  //   }
  // }
};
