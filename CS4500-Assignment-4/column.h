#include "array.h"
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
class Column : public Object {
public:
  Vec *val_;
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
};

/*************************************************************************
 * BoolColumn::
 * Holds bool values.
 */
class BoolColumn : public Column {
public:
  Bvec *val_;

  BoolColumn() { val_ = new Bvec(); }
  BoolColumn(int n, ...) {
    val_ = new Bvec();
    va_list vl;
    bool val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, bool);
      val_->append(val);
    }
    va_end(vl);
  }

  bool get(size_t idx) { return val_->get_bool(idx); }

  BoolColumn *as_bool() { return this; }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, bool val) { val_->set(idx, val); }

  size_t size() { return val_->size; }
  char type_check() { return 'B'; }
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
};
