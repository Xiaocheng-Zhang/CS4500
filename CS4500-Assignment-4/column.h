#pragma once

#include "object.h"
#include "string.h"
#include "vec.h"
#include <iostream>
#include <stdarg.h>

/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class IntColumn;
class BoolColumn;
class FloatColumn;
class StringColumn;
class Column : public Object {
public:
  Vec *val_;
  Column() : Object() { val_ = nullptr; }
  /** Type converters: Return same column under its actual type, or
   *  nullptr if of the wrong type.  */
  virtual IntColumn *as_int() { return nullptr; }
  virtual BoolColumn *as_bool() { return nullptr; }
  virtual FloatColumn *as_float() { return nullptr; }
  virtual StringColumn *as_string() { return nullptr; }

  /** Type appropriate push_back methods. Calling the wrong method is
   * undefined behavior. **/
  virtual void push_back(int val) {
    abstract_error_print("column.h", "Column", "push_back(int val)");
  }
  virtual void push_back(bool val) {
    abstract_error_print("column.h", "Column", "push_back(bool val)");
  }
  virtual void push_back(float val) {
    abstract_error_print("column.h", "Column", "push_back(float val)");
  }
  virtual void push_back(String *val) {
    abstract_error_print("column.h", "Column", "push_back(String *val)");
  }

  /** Returns the number of elements in the column. */
  virtual size_t size() { return 0; }

  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  char get_type() { return type_check(); }

  virtual char type_check() { return ' '; }
};

/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
public:
  IntColumn() : Column() { val_ = new Ivec(); }

  IntColumn(int n, ...) : Column() {
    val_ = new Ivec();
    va_list vl;
    int val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, int);
      val_->append(val);
    }
    va_end(vl);
  }

  int get(size_t idx) { return val_->get_int(idx); }

  IntColumn *as_int() {
    IntColumn *temp = new IntColumn();
    temp->val_ = val_->copy();
    return temp;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) { val_->set(idx, val); }

  size_t size() { return val_->size_; }

  char type_check() { return 'I'; }

  void push_back(int i) {
    val_->append(i);
  }
};

/*************************************************************************
 * BoolColumn::
 * Holds bool values.
 */
class BoolColumn : public Column {
public:
  Bvec *val_;

  BoolColumn() : Column() { val_ = new Bvec(); }
  BoolColumn(int n, ...) : Column() {
    val_ = new Bvec();
    va_list vl;
    bool val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, int);
      val_->append(val);
    }
    va_end(vl);
  }

  bool get(size_t idx) { return val_->get_bool(idx); }

  BoolColumn *as_bool() { return this; }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, bool val) { val_->set(idx, val); }

  size_t size() { return val_->size_; }
  char type_check() { return 'B'; }
  void push_back(bool b) { val_->append(b); }
};

/*************************************************************************
 * FloatColumn::
 * Holds float values.
 */
class FloatColumn : public Column {
public:
  FloatColumn() : Column() { val_ = new Fvec(); }
  FloatColumn(int n, ...) : Column() {
    val_ = new Fvec();
    va_list vl;
    float val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, float);
      val_->append(val);
    }
    va_end(vl);
  }

  float get(size_t idx) { return val_->get_float(idx); }

  FloatColumn *as_float() { return this; }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, float val) { val_->set(idx, val); }

  size_t size() { return val_->size_; }

  char type_check() { return 'F'; }

  void push_back(float f) { val_->append(f); }
};

// Other primitive column classes similar...

/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
public:
  StringColumn() : Column() { val_ = new Svec(); }
  StringColumn(int n, ...) : Column() {
    val_ = new Svec();
    va_list vl;
    String *val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, String *);
      val_->append(val);
    }
    va_end(vl);
  }

  StringColumn *as_string() { return this; }

  /** Returns the string at idx; undefined on invalid idx.*/
  String *get(size_t idx) { return val_->get_String(idx); }

  /** Out of bound idx is undefined. */
  void set(size_t idx, String *val) { val_->set(idx, val); }

  size_t size() { return val_->size_; }
  char type_check() { return 'S'; }

  void push_back(String* s) { val_->append(s); }
};

class ColumnVec : public Object {
public:
  size_t size_;
  size_t capacity_;
  size_t hash_;
  Column **list_;

  ColumnVec() {
    size_ = 0;
    capacity_ = 4;
    hash_ = 0;
    list_ = new Column *[capacity_];
    initialize(0);
  }

  ~ColumnVec() { delete[] list_; }

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

  virtual void append(Column *col) {
    expand();
    Column *colcpy = new Column();
    colcpy->val_ = col->val_->copy();
    list_[size_] = colcpy;
    size_++;
  }

  virtual void set(size_t idx, Column *col) {
    expand();
    Column *colcpy = new Column();
    colcpy->val_ = col->val_->copy();
    list_[idx] = colcpy; // v->copy();
  }

  virtual void insert(size_t idx, Column *col) {
    expand();
    Column **temp = new Column *[capacity_];
    size_++;
    for (size_t i = 0, j = idx; i < size_; i++) {
      if (i < j) {
        temp[i] = list_[i];
      } else if (i == j) {
        Column *colcpy = new Column();
        colcpy->val_ = col->val_->copy();
        temp[i] = colcpy; // v->copy();
      } else {
        temp[i] = list_[j];
        j++;
      }
    }
    delete[] list_;
    list_ = temp;
  }
  virtual bool contains(Column *col) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m]->equals(col)) {
        return true;
      }
    }
    return false;
  }

  virtual int indexAt(Column *col) {
    for (size_t m = 0; m < size_; m++) {
      if (list_[m]->equals(col)) {
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
  virtual ColumnVec *copy() {
    ColumnVec *temp = new ColumnVec();
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

  virtual Column *get_Column(size_t index) {
    assert(index < size_ && index >= 0);
    return list_[index];
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