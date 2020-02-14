#pragma once
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "string.h"

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
    abstract_error_print("vec.h", "Vec", "append(char c)");
  }
  virtual void append(float f) {
    abstract_error_print("vec.h", "Vec", "append(float c)");
  }
  virtual void append(int i) {
    abstract_error_print("vec.h", "Vec", "append(int c)");
  }
  virtual void append(bool b) {
    abstract_error_print("vec.h", "Vec", "append(bool b)");
  }
  virtual void append(String *s) {
    abstract_error_print("vec.h", "Vec", "append(String c)");
  }
  // virtual void append(Column *col) {
  //   abstract_error_print("vec.h", "Vec", "append(Column col)");
  // }
  virtual void set(size_t idx, char c) {
    abstract_error_print("vec.h", "Vec", "set(size_t idx, char c)");
  }
  virtual void set(size_t idx, float f) {
    abstract_error_print("vec.h", "Vec", "set(size_t idx, float f)");
  }
  virtual void set(size_t idx, int i) {
    abstract_error_print("vec.h", "Vec", "set(size_t idx, int i)");
  }
  virtual void set(size_t idx, bool b) {
    abstract_error_print("vec.h", "Vec", "set(size_t idx, bool b)");
  }
  virtual void set(size_t idx, String *s) {
    abstract_error_print("vec.h", "Vec", "set(size_t idx, String *s)");
  }
  // virtual void set(size_t idx, Column *col) {
  //   abstract_error_print("vec.h", "Vec", "set(size_t idx, Column *col)");
  // }
  virtual void insert(size_t idx, char c) {
    abstract_error_print("vec.h", "Vec", "insert(size_t idx, char c)");
  }
  virtual void insert(size_t idx, float f) {
    abstract_error_print("vec.h", "Vec", "insert(size_t idx, float f)");
  }
  virtual void insert(size_t idx, int i) {
    abstract_error_print("vec.h", "Vec", "insert(size_t idx, int i)");
  }
  virtual void insert(size_t idx, bool b) {
    abstract_error_print("vec.h", "Vec", "insert(size_t idx, bool b)");
  }
  virtual void insert(size_t idx, String *s) {
    abstract_error_print("vec.h", "Vec", "insert(size_t idx, String *s)");
  }
  // virtual void insert(size_t idx, Column *col) {
  //   abstract_error_print("vec.h", "Vec", "insert(size_t idx, Column *col)");
  // }
  virtual bool contains(char c) {
    abstract_error_print("vec.h", "Vec", "contains(char c)");
    return false;
  }
  virtual bool contains(float f) {
    abstract_error_print("vec.h", "Vec", "contains(float f)");
    return false;
  }
  virtual bool contains(int i) {
    abstract_error_print("vec.h", "Vec", "contains(int i)");
    return false;
  }
  virtual bool contains(bool b) {
    abstract_error_print("vec.h", "Vec", "contains(bool b)");
    return false;
  }
  virtual bool contains(String *s) {
    abstract_error_print("vec.h", "Vec", "contains(String *s)");
    return false;
  }
  // virtual bool contains(Column *col) {
  //   abstract_error_print("vec.h", "Vec", "contains(Column *col)");
  //   return false;
  // }
  virtual int indexAt(char c) {
    abstract_error_print("vec.h", "Vec", "indexAt(char c)");
    return -1;
  }
  virtual int indexAt(float f) {
    abstract_error_print("vec.h", "Vec", "indexAt(float f)");
    return -1;
  }
  virtual int indexAt(int i) {
    abstract_error_print("vec.h", "Vec", "indexAt(int i)");
    return -1;
  }
  virtual int indexAt(bool b) {
    abstract_error_print("vec.h", "Vec", "indexAt(bool b)");
    return false;
  }
  virtual int indexAt(String *s) {
    abstract_error_print("vec.h", "Vec", "indexAt(String *s)");
    return -1;
  }
  // virtual int indexAt(Column *col) {
  //   abstract_error_print("vec.h", "Vec", "indexAt(Column *col)");
  //   return -1;
  // }
  virtual void del(size_t idx) {
    abstract_error_print("vec.h", "Vec", "del(size_t idx)");
  }
  virtual Vec *copy() {
    abstract_error_print("vec.h", "Vec", "copy()");
    return nullptr;
  }
  virtual int get_int(size_t idx) {
    abstract_error_print("vec.h", "Vec", "get_int(size_t idx)");
    return 0;
  }
  virtual char get_char(size_t idx) {
    abstract_error_print("vec.h", "Vec", "get_char(size_t idx)");
    return ' ';
  }
  virtual float get_float(size_t idx) {
    abstract_error_print("vec.h", "Vec", "get_float(size_t idx)");
    return 0;
  }
  virtual bool get_bool(size_t idx) {
    abstract_error_print("vec.h", "Vec", "get_bool(size_t idx)");
    return false;
  }
  virtual String *get_String(size_t idx) {
    abstract_error_print("vec.h", "Vec", "get_String(size_t idx)");
    return nullptr;
  }
  // virtual Column *get_Column(size_t idx) {
  //   abstract_error_print("vec.h", "Vec", "get_Column(size_t idx)");
  //   return nullptr;
  // }
  virtual size_t size() { return size_; }
  virtual void print_self() {
    puts(
        "invalid function call in vec.h: vec is an abstract class: print_self");
  }

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    return false;
  }
};

class Cvec : public Vec {
public:
  char *list_;

  Cvec() : Vec() { list_ = new char[capacity_]; }

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

  virtual char get_char(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return list_[idx];
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

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Vec *temp = dynamic_cast<Vec *>(object);
    if (!temp) {
      return false;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if (temp->get_char(i) != list_[i]) {
          return false;
        }
      }
    }
  }
};

class Bvec : public Vec {
public:
  bool *list_;

  Bvec() : Vec() { list_ = new bool[capacity_]; }

  ~Bvec() { delete[] list_; }

  void expand() {
    if (size_ == capacity_) {
      capacity_ *= 2;
      bool *temp = new bool[capacity_];
      for (size_t i = 0; i < size_; i++) {
        temp[i] = list_[i];
      }
      delete[] list_;
      list_ = temp;
    }
    assert(size_ < capacity_);
  }

  virtual void append(bool b) {
    expand();
    list_[size_] = b;
    size_++;
  }

  virtual void set(size_t idx, bool b) {
    expand();
    list_[idx] = b;
  }

  virtual void insert(size_t idx, bool b) {
    expand();
    bool *temp = new bool[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        temp[i] = b;
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }

  virtual bool contains(bool b) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == b) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(bool b) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m] == b) {
        return m;
      }
    }
    return -1;
  }

  virtual void del(size_t idx) {
    bool *temp = new bool[capacity_];
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
    Vec *temp = new Bvec();
    for (size_t i = 0; i < size_; i++) {
      temp->append(list_[i]);
    }
    return temp;
  }

  virtual bool get_bool(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return list_[idx];
  }
  /**
   * overrite hash_me to hash the code.
   * @return return hash code.
   */
  virtual size_t hash_me() {
    for (size_t i = 0; i < size_; i++) {
      if (list_[i]) {
        hash_ = hash_ * 67 + 13;
      } else {
        hash_ = hash_ * 67 + 2;
      }
    }
    return hash_;
  }

  virtual void print_self() {
    for (size_t i = 0; i < size_; i++) {
      printf("%d", list_[i]);
    }
  }

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Vec *temp = dynamic_cast<Vec *>(object);
    if (!temp) {
      return false;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if (temp->get_bool(i) != list_[i]) {
          return false;
        }
      }
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
  virtual float get_float(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return list_[idx];
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

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Vec *temp = dynamic_cast<Vec *>(object);
    if (!temp) {
      return false;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if (temp->get_float(i) != list_[i]) {
          return false;
        }
      }
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

  virtual int get(size_t index) {
    assert(index < size_ && index >= 0);
    return list_[index];
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
  virtual int get_int(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return list_[idx];
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

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Vec *temp = dynamic_cast<Vec *>(object);
    if (!temp) {
      return false;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if (temp->get_int(i) != list_[i]) {
          return false;
        }
      }
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
  virtual String *get_String(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return list_[idx];
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

  virtual bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Vec *temp = dynamic_cast<Vec *>(object);
    if (!temp) {
      return false;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if (temp->get_String(i) != list_[i]) {
          return false;
        }
      }
    }
  }
};
