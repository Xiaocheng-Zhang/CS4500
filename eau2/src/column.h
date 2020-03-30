#pragma once
#include <iostream>
#include <type_traits>
#include <vector>

#include "object.h"
#include "string.h"
#include "typedef.h"
using namespace std;

/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. 
 * 
 * Reduced code duplication ::
 * Our column has been refactored by using vector from c++ library. This helped
 * us get rid of our self-created vector class. The setter and getter method has
 * also been shortened. Type convert functions such as as_int, as_bool are also 
 * removed.
 * */
class Column : public Object {
public:

  /** Type appropriate push_back methods. Calling the wrong method is
   * undefined behavior. **/
  virtual void push_back(int val) {}
  virtual void push_back(bool val) {}
  virtual void push_back(float val) {}
  virtual void push_back(String *val) {}

  /** Set the data in the corresponding column */
  virtual void set(size_t idx, int val) {}
  virtual void set(size_t idx, bool val) {}
  virtual void set(size_t idx, float val) {}
  virtual void set(size_t idx, String *val) {}

  /** Returns the number of elements in the column. */
  virtual size_t size() = 0;

  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  virtual char get_type() = 0;

  /** Get the data in the corresponding column */
  virtual int get_int(size_t idx) { return 0; }
  virtual bool get_bool(size_t idx) { return 0; }
  virtual String *get_string(size_t idx) { return nullptr; }
  virtual float get_float(size_t idx) { return 0; }
  virtual void print_self() {}
};

/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
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

/*************************************************************************
 * BoolColumn::
 * Holds bool values.
 */
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

/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
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

/*************************************************************************
 * FloatColumn::
 * Holds float values.
 */
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
