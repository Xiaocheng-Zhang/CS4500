#include <iostream>
#include <stdarg.h> 
#include "vec.h"
#include "object.h"
#include "string.h"
#include "array.h"


/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class Column : public Object {
 public: 
  /** Type converters: Return same column under its actual type, or
   *  nullptr if of the wrong type.  */
  virtual IntColumn* as_int() {
    return nullptr;
  }
  virtual BoolColumn*  as_bool() {
    return nullptr;
  }
  virtual FloatColumn* as_float() {
    return nullptr;
  }
  virtual StringColumn* as_string() {
    return nullptr;
  }
 
  /** Type appropriate push_back methods. Calling the wrong method is
    * undefined behavior. **/
  virtual void push_back(int val) {
    std::cout << "Wrong Type. Int Type Expected." << std::endl;
    exit(0);
  }
  virtual void push_back(bool val) {
    std::cout << "Wrong Type. Bool Type Expected." << std::endl;
    exit(0);
  }
  virtual void push_back(float val) {
    std::cout << "Wrong Type. Float Type Expected." << std::endl;
    exit(0);
  }
  virtual void push_back(String* val) {
    std::cout << "Wrong Type. String Type Expected." << std::endl;
    exit(0);
  }
 
 /** Returns the number of elements in the column. */
  virtual size_t size() {
    return 0;
  }
 
  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  virtual char get_type() {
    return ' ';
  }
};
 
/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
 public:
  Ivec* val_;

  IntColumn() {
    val_ = new Ivec();
  }

  IntColumn(int n, ...) {
    val_ = new Ivec();
    va_list vl;
    int val;
    va_start(vl,n);
    for (int i = 0; i < n; i++) {
      val=va_arg(vl,int);
      val_->append(val);
    }
    va_end(vl);
  }

  int get(size_t idx) {
    return val_->get(idx);
  }

  IntColumn* as_int() {
    return this;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {
    val_->set(idx, val);
  }

  size_t size() {
    return val_->size_;
  }
  char get_type() {
    return 'I';
  }
};

/*************************************************************************
 * BoolColumn::
 * Holds bool values.
 */
class BoolColumn : public Column {
 public:
  Bvec* val_;

  BoolColumn() {
    val_ = new Bvec();
  }
  BoolColumn(int n, ...) {
    val_ = new Bvec();
    va_list vl;
    bool val;
    va_start(vl,n);
    for (int i = 0; i < n; i++) {
      val=va_arg(vl,bool);
      val_->append(val);
    }
    va_end(vl);
  }


  bool get(size_t idx) {
    return val_->get(idx);
  }

  BoolColumn* as_bool() {
    return this;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, bool val) {
    val_->set(idx,val);
  }

  size_t size() {
    return val_->size;
  }
  char get_type() {
    return 'B';
  }
};

/*************************************************************************
 * FloatColumn::
 * Holds float values.
 */
class FloatColumn : public Column {
 public:
  Fvec* val_;

  FloatColumn() {
    val_ = new Fvec();
  }
  FloatColumn(int n, ...) {
    val_ = new Fvec();
    va_list vl;
    float val;
    va_start(vl,n);
    for (int i = 0; i < n; i++) {
      val=va_arg(vl,float);
      val_->append(val);
    }
    va_end(vl);
  }

  float get(size_t idx) {
    return val_->get(idx);
  }

  FloatColumn* as_float() {
    return this;
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, float val) {
    val_->set(idx,val);
  }

  size_t size() {
    return val_->size_;
  }

  char get_type() {
    return 'F';
  }
};


 
// Other primitive column classes similar...
 
/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
 public:
  Svec* val_;

  StringColumn() {
    val_ = new Svec();
  }
  StringColumn(int n, ...) {
    val_ = new Svec();
    va_list vl;
    String* val;
    va_start(vl,n);
    for (int i = 0; i < n; i++) {
      val=va_arg(vl,String*);
      val_->append(val);
    }
    va_end(vl);
  }


  StringColumn* as_string() {
    return this;
  }

  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx) {
    return val_->get(idx);
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val) {
    val_->set(idx, val);
  }

  size_t size() {
    return val_->size_;
  }
  char get_type() {
    return 'S';
  }
};
