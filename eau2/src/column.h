#pragma once
#include <iostream>
#include <type_traits>
#include <vector>

#include "object.h"
#include "string.h"
#include "typedef.h"
using namespace std;

class Column : public Object {
public:
  virtual void push_back(int val) {}
  virtual void push_back(bool val) {}
  virtual void push_back(float val) {}
  virtual void push_back(String *val) {}

  virtual void set(size_t idx, int val) {}
  virtual void set(size_t idx, bool val) {}
  virtual void set(size_t idx, float val) {}
  virtual void set(size_t idx, String *val) {}

  virtual size_t size() = 0;

  virtual char get_type() = 0;

  virtual int get_int(size_t idx) { return 0; }
  virtual bool get_bool(size_t idx) { return 0; }
  virtual String *get_string(size_t idx) { return nullptr; }
  virtual float get_float(size_t idx) { return 0; }
  virtual void print_self() {}
};

class IntColumn : public Column {
private:
  vector<int> vec;

public:
  IntColumn() : Column() {}
  ~IntColumn() {}
  void push_back(int val) { vec.push_back(val); }
  void set(size_t idx, int val) {
    auto index = vec.begin() + idx;
    vec.insert(index, val);
  }
  size_t size() { return vec.size(); }
  char get_type() { return INTEGER_C; }
  int get_int(size_t idx) { return vec[idx]; }
  void print_self() {
    for (size_t i = 0; i < size(); i++) {
      cout << get_int(i) << ' ';
    }
    cout << "\n";
  }
};

class BoolColumn : public Column {
private:
  vector<bool> vec;

public:
  BoolColumn() : Column() {}
  ~BoolColumn() {}
  void push_back(bool val) { vec.push_back(val); }
  void set(size_t idx, bool val) {
    auto index = vec.begin() + idx;
    vec.insert(index, val);
  }
  size_t size() { return vec.size(); }
  char get_type() { return BOOL_C; }
  bool get_bool(size_t idx) { return vec[idx]; }
  void print_self() {
    for (size_t i = 0; i < size(); i++) {
      cout << get_bool(i) << ' ';
    }
    cout << "\n";
  }
};

class StringColumn : public Column {
private:
  vector<String *> vec;

public:
  StringColumn() : Column() {}
  ~StringColumn() {}
  void push_back(String *val) { vec.push_back(val); }
  void set(size_t idx, String *val) {
    auto index = vec.begin() + idx;
    vec.insert(index, val);
  }
  size_t size() { return vec.size(); }
  char get_type() { return STRING_C; }
  String *get_string(size_t idx) {
    if (!vec[idx]) {
      return nullptr;
    }
    String *tmp = new String(vec[idx]->c_str());
    return tmp;
  }
  void print_self() {
    for (size_t i = 0; i < size(); i++) {
      cout << get_string(i)->c_str() << ' ';
    }
    cout << "\n";
  }
};

class FloatColumn : public Column {
private:
  vector<float> vec;

public:
  FloatColumn() : Column() {}
  ~FloatColumn() {}
  void push_back(float val) { vec.push_back(val); }
  void set(size_t idx, float val) {
    auto index = vec.begin() + idx;
    vec.insert(index, val);
    // vec[idx] = val;
  }
  size_t size() { return vec.size(); }
  char get_type() { return FLOAT_C; }
  float get_float(size_t idx) {
    return vec[idx];
  }
  void print_self() {
    for (size_t i = 0; i < size(); i++) {
      cout << get_float(i) << ' ';
    }
    cout << "\n";
  }
};
