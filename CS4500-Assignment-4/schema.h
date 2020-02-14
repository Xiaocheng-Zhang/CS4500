#include "object.h"
#include "vec.h"
#include <assert.h>

static const size_t INTEGER = 0;
static const size_t FLOAT = 1;
static const size_t BOOLEAN = 2;
static const size_t STRING = 3;

/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
public:
  Vec *type_vec;
  Vec *col_name_vec;
  Vec *row_name_vec;

  /** Copying constructor */
  Schema(Schema &from) {
    type_vec = from.type_vec->copy();
    col_name_vec = from.col_name_vec->copy();
    row_name_vec = from.row_name_vec->copy();
  }

  /** Create an empty schema **/
  Schema() {
    type_vec = new Cvec();
    col_name_vec = new Svec();
    row_name_vec = new Svec();
  }

  /** Create a schema from a string of types. A string that contains
   * characters other than those identifying the four type results in
   * undefined behavior. The argument is external, a nullptr argument is
   * undefined. **/
  Schema(const char *types) {
    if (types == nullptr) {
      std::cout << "The variable should not be null" << std::endl;
      exit(1);
    }
    type_vec = new Cvec();
    col_name_vec = new Svec();
    row_name_vec = new Svec();
    for (size_t i = 0; i < strlen(types); i++) {
      // if (types[i] == 'I') {
      //   type_vec->append('I');
      //   col_name_vec->append(nullptr);
      // } else if (types[i] == 'B') {
      //   type_vec->append('B');
      //   col_name_vec->append(nullptr);
      // } else if (types[i] == 'F') {
      //   type_vec->append('F');
      //   col_name_vec->append(nullptr);
      // } else if (types[i] == 'S') {
      //   type_vec->append('S');
      //   col_name_vec->append(nullptr);
      // }
      if (type_check(types[i])) {
        type_vec->append(types[i]);
        col_name_vec->size_++;
      } else {
        std::cout << "The variable should not contain other than four "
                     "identifying type"
                  << std::endl;
        exit(1);
      }
    }
  }

  bool type_check(char c) {
    return c == 'I' || c == 'B' || c == 'F' || c == 'S';
  }

  /** Add a column of the given type and name (can be nullptr), name
   * is external. Names are expectd to be unique, duplicates result
   * in undefined behavior. */
  void add_column(char typ, String *name) {
    assert(typ != NULL);
    assert(type_check(typ));
    assert(!col_name_vec->contains(name));
    type_vec->append(typ);
    col_name_vec->append(name);
  }

  /** Add a row with a name (possibly nullptr), name is external.  Names are
   *  expectd to be unique, duplicates result in undefined behavior. */
  void add_row(String *name) {
    assert(!row_name_vec->contains(name));
    row_name_vec->append(name);
  }

  /** Return name of row at idx; nullptr indicates no name. An idx >= width
   * is undefined. */
  String *row_name(size_t idx) {
    assert(idx < row_name_vec->size_);
    return row_name_vec->get_String(idx);
  }

  /** Return name of column at idx; nullptr indicates no name given.
   *  An idx >= width is undefined.*/
  String *col_name(size_t idx) {
    assert(idx < col_name_vec->size_);
    return col_name_vec->get_String(idx);
  }

  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    assert(idx < type_vec->size_);
    return type_vec->get_char(idx);
  }

  /** Given a column name return its index, or -1. */
  int col_idx(const char *name) {
    return col_name_vec->indexAt(new String(name));
  }

  /** Given a row name return its index, or -1. */
  int row_idx(const char *name) {
    return row_name_vec->indexAt(new String(name));
  }

  /** The number of columns */
  size_t width() { return col_name_vec->size_; }

  /** The number of rows */
  size_t length() { return row_name_vec->size_; }
};

/** cannot mutate value inside*/
class Buffer : public Object {
public:
  size_t type_;
  int int_ = 0;
  float f_ = 0;
  bool b_ = false;
  String *s_ = nullptr;

  Buffer(int i) : Object() {
    type_ = INTEGER;
    int_ = i;
  }
  Buffer(float f) : Object() {
    type_ = FLOAT;
    f_ = f;
  }
  Buffer(bool b) : Object() {
    type_ = BOOLEAN;
    b_ = b;
  }
  Buffer(String *s) : Object() {
    type_ = STRING;
    s_ = s;
  }

  size_t hash_me() { return type_; }

  bool equals(Object *object) {
    if (hash() == object->hash()) {
      return true;
    }
    Buffer *buf = dynamic_cast<Buffer *>(object);
    if (buf) {
      if (buf->type_ == type_) {
        switch (type_) {
        case INTEGER:
          return int_ == buf->int_;
        case FLOAT:
          return f_ == buf->f_;
        case BOOLEAN:
          return b_ == buf->b_;
        case STRING:
          return s_ == buf->s_;
        default:
          return false;
        }
      }
    }
    return false;
  }

  int get_int() {
    assert(type_ == INTEGER);
    return int_;
  }
  float get_float() {
    assert(type_ == FLOAT);
    return f_;
  }
  bool get_bool() {
    assert(type_ == BOOLEAN);
    return b_;
  }
  String* get_String() {
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
  /** Called before visiting a row, the argument is the row offset in the
    dataframe. */
  virtual void start(size_t r) {}

  /** Called for fields of the argument's type with the value of the field.
   */
  virtual void accept(bool b) {}
  virtual void accept(float f) {}
  virtual void accept(int i) {}
  virtual void accept(String *s) {}

  /** Called when all fields have been seen. */
  virtual void done() {}
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
public:
  /** Build a row following a schema. */
  Vec *type_vec;
  Buffer **buffer_array;
  size_t size_;
  Row(Schema &scm) { 
    size_ == scm.type_vec->size();
    type_vec = scm.type_vec; 
    buffer_array = new Buffer*[size_];
    initialize();
    }

  void initialize() {
    for (size_t i = 0; i < size_; i++) {
      buffer_array[i] = nullptr;
    }
  }
  /** Setters: set the given column with the given value. Setting a column
   * with a value of the wrong type is undefined. */
  void set(size_t col, int val) {
    assert(type_vec->get_char(col) == 'I');
    buffer_array[col] = new Buffer(val);
  }
  void set(size_t col, float val) {
    assert(type_vec->get_char(col) == 'F');
    buffer_array[col] = new Buffer(val);
  }
  void set(size_t col, bool val) {
    assert(type_vec->get_char(col) == 'B');
    buffer_array[col] = new Buffer(val);
  }
  /** The string is external. */
  void set(size_t col, String *val) {
    assert(type_vec->get_char(col) == 'S');
    buffer_array[col] = new Buffer(val);
  }

  /** Set/get the index of this row (ie. its position in the dataframe. This
   * is only used for informational purposes, unused otherwise */
  void set_idx(size_t idx);
  size_t get_idx();

  /** Getters: get the value at the given column. If the column is not
   * of the requested type, the result is undefined. */
  int get_int(size_t col);
  bool get_bool(size_t col);
  float get_float(size_t col);
  String *get_string(size_t col);

  /** Number of fields in the row. */
  size_t width();

  /** Type of the field at the given position. An idx >= width is
     undefined. */
  char col_type(size_t idx);

  /** Given a Fielder, visit every field of this row. The first argument is
   * index of the row in the dataframe.
   * Calling this method before the row's fields have been set is undefined.
   */
  void visit(size_t idx, Fielder &f);
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
  virtual bool accept(Row &r);

  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  void join_delete(Rower *other);
};
