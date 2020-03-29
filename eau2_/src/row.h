#pragma once
#include <iostream>
#include <vector>

#include "object.h"
#include "schema.h"
#include "string.h"
#include "typedef.h"

using namespace std;

/** cannot mutate value inside*/
class RowBuffer : public Object {
private:
  int type_;
  int int_;
  float f_;
  bool b_;
  String *s_;

public:
  RowBuffer(int i) : Object() {
    type_ = INTEGER;
    int_ = i;
  }
  RowBuffer(float f) : Object() {
    type_ = FLOAT;
    f_ = f;
  }
  RowBuffer(bool b) : Object() {
    type_ = BOOL;
    b_ = b;
  }
  RowBuffer(String *s) : Object() {
    type_ = STRING;
    s_ = s;
  }

  int get_type() { return type_; }

  int get_int() {
    assert(type_ == INTEGER);
    return int_;
  }
  float get_float() {
    assert(type_ == FLOAT);
    return f_;
  }
  bool get_bool() {
    assert(type_ == BOOL);
    return b_;
  }
  String *get_String() {
    assert(type_ == STRING);
    return new String(*s_);
  }
};

/*****************************************************************************
 * Fielder::
 * A field vistor invoked by Row.
 */
class Fielder : public Object {
public:
  size_t start_;
  bool end_;
  /** Called before visiting a row, the argument is the row offset in the
    dataframe. */
  virtual void start(size_t r) { start_ = r; }

  /** Called for fields of the argument's type with the value of the field.
   */
  virtual void accept(bool b) {}
  virtual void accept(float f) {}
  virtual void accept(int i) {}
  virtual void accept(String *s) {}

  /** Called when all fields have been seen. */
  virtual void done() { end_ = true; }

  virtual Object *clone() { return new Fielder(); }
};

/*************************************************************************
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * dataframe's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a dataframe hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
private:
  vector<char> type_vec;
  RowBuffer **buffer_array;
  size_t size_;
  size_t index_;

public:
  /** Build a row following a schema. */

  Row(Schema &scm) : Object() {
    size_ = scm.width();
    buffer_array = new RowBuffer *[size_];
    type_vec = scm.type_vec;
    index_ = 0;
    initialize();
  }

  ~Row() { delete[] buffer_array; }

  void initialize() {
    for (size_t i = 0; i < size_; i++) {
      buffer_array[i] = nullptr;
    }
  }

  /** Setters: set the given column with the given value. Setting a column
   * with a value of the wrong type is undefined. */
  void set(size_t col, int val) {
    assert(type_vec[col] == INTEGER_C);
    buffer_array[col] = new RowBuffer(val);
  }
  void set(size_t col, float val) {
    assert(type_vec[col] == FLOAT_C);
    buffer_array[col] = new RowBuffer(val);
  }
  void set(size_t col, bool val) {
    assert(type_vec[col] == BOOL_C);
    buffer_array[col] = new RowBuffer(val);
  }
  /** The string is external. */
  void set(size_t col, String *val) {
    assert(type_vec[col] == STRING_C);
    buffer_array[col] = new RowBuffer(val);
  }

  /** Set/get the index of this row (ie. its position in the dataframe. This
   * is only used for informational purposes, unused otherwise */
  void set_idx(size_t idx) { index_ = idx; }
  size_t get_idx() { return index_; }

  /** Getters: get the value at the given column. If the column is not
   * of the requested type, the result is undefined. */
  int get_int(size_t col) {
    assert(buffer_array[col]->get_type() == INTEGER);
    return buffer_array[col]->get_int();
  }
  bool get_bool(size_t col) {
    assert(buffer_array[col]->get_type() == BOOL);
    return buffer_array[col]->get_bool();
  }
  float get_float(size_t col) {
    assert(buffer_array[col]->get_type() == FLOAT);
    return buffer_array[col]->get_float();
  }
  String *get_string(size_t col) {
    assert(buffer_array[col]->get_type() == STRING);
    return buffer_array[col]->get_String();
  }

  /** Number of fields in the row. */
  size_t width() { return size_; }

  /** Type of the field at the given position. An idx >= width is
     undefined. */
  char col_type(size_t idx) {
    assert(idx < size_ && idx >= 0);
    return type_vec[idx];
  }

  bool check_schema(Schema &schema) {
    if (schema.width() != type_vec.size())
      return false;
    for (size_t i = 0; i < type_vec.size(); i++) {
      if (type_vec[i] != schema.col_type(i))
        return false;
    }
    return true;
  }
  /** Given a Fielder, visit every field of this row. The first argument is
   * index of the row in the dataframe.
   * Calling this method before the row's fields have been set is undefined.
   */
  void visit(size_t idx, Fielder &f) {
    assert(idx >= 0 && idx < size_);
    f.start(idx);
    switch (buffer_array[idx]->get_type()) {
    case INTEGER:
      f.accept(buffer_array[idx]->get_int());
      break;
    case FLOAT:
      f.accept(buffer_array[idx]->get_float());
      break;
    case BOOL:
      f.accept(buffer_array[idx]->get_bool());
      break;
    case STRING:
      f.accept(buffer_array[idx]->get_String());
      break;
    }
    f.done();
  }
};

/*******************************************************************************
 *  Rower::
 *  An interface for iterating through each row of a data frame. The intent
 *  is that this class should subclassed and the accept() method be given
 *  a meaningful implementation. Rowers can be cloned for parallel execution.
 */
class Rower : public Object {
public:
  /** This method is called once per row. The row object is on loan and
      should not be retained as it is likely going to be reused in the next
      call. The return value is used in filters to indicate that a row
      should be kept. */
  virtual bool accept(Row &r) { return false; }

  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower *other) {}
};
