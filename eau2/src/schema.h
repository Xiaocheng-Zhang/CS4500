#pragma once
#include <cstring>
#include <iostream>
#include <vector>

#include "object.h"
#include "string.h"

using namespace std;

class Schema : public Object {
private:
  vector<char> type_vec;
  vector<String *> col_name_vec;
  vector<String *> row_name_vec;

public:
  /** Copying constructor */
  Schema(Schema &from) {
    type_vec = from.clone_type();
    col_name_vec = from.clone_col_name();
    row_name_vec = from.clone_row_name();
  }

  /** Create an empty schema **/
  Schema() {}

  /** Create a schema from a string of types. A string that contains
   * characters other than those identifying the four type results in
   * undefined behavior. The argument is external, a nullptr argument is
   * undefined. **/
  Schema(const char *types) {
    if (types == nullptr) {
      std::cout << "The variable should not be null" << std::endl;
      exit(1);
    }
    for (size_t i = 0; i < strlen(types); i++) {
      char c = types[i];
      if (type_check(c)) {
        type_vec.push_back(c);
        col_name_vec.push_back(nullptr);
      }
    }
  }

  ~Schema() {}

  bool type_check(char typ) {
    return typ == 'I' || typ == 'B' || typ == 'S' || typ == 'F';
  }

  vector<char> clone_type() {
    vector<char> tmp;
    for (size_t i = 0; i < type_vec.size(); i++) {
      char c = type_vec[i];
      tmp.push_back(c);
    }
    return tmp;
  }
  vector<String *> clone_col_name() {
    vector<String *> tmp;
    for (size_t i = 0; i < type_vec.size(); i++) {
      String *s = col_name_vec[i];
      tmp.push_back(s);
    }
    return tmp;
  }
  vector<String *> clone_row_name() {
    vector<String *> tmp;
    for (int i = 0; i < type_vec.size(); i++) {
      String *s = row_name_vec[i];
      tmp.push_back(s);
    }
    return tmp;
  }

  bool contains(vector<String *> vec, String *name) {
    for (size_t i = 0; i < vec.size(); i++) {
      if (&(vec[i]) == &name) {
        return true;
      }
    }
    return false;
  }

  /** Add a column of the given type and name (can be nullptr), name
   * is external. Names are expectd to be unique, duplicates result
   * in undefined behavior. */
  void add_column(char typ, String *name) {
    assert(type_check(typ));
    type_vec.push_back(typ);
    assert(!contains(col_name_vec, name));
    col_name_vec.push_back(name);
  }

  /** Add a row with a name (possibly nullptr), name is external.  Names are
   *  expectd to be unique, duplicates result in undefined behavior. */
  void add_row(String *name) {
    assert(!contains(row_name_vec, name));
    row_name_vec.push_back(name);
  }

  /** Return name of row at idx; nullptr indicates no name. An idx >= width
   * is undefined. */
  String *row_name(size_t idx) {
    assert(idx < row_name_vec.size());
    return row_name_vec[idx];
  }

  /** Return name of column at idx; nullptr indicates no name given.
   *  An idx >= width is undefined.*/
  String *col_name(size_t idx) {
    assert(idx < col_name_vec.size());
    return col_name_vec[idx];
  }

  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    assert(idx < col_name_vec.size());
    return type_vec[idx];
  }

  /** Given a column name return its index, or -1. */
  int col_idx(const char *name) {
    String s(name);
    for (size_t i = 0; i < type_vec.size(); i++) {
      String *current = col_name_vec[i];
      if (current != nullptr && *current == s) {
        return i;
      }
    }
    return -1;
  }

  /** Given a row name return its index, or -1. */
  int row_idx(const char *name) {
    String s(name);
    for (size_t i = 0; i < row_name_vec.size(); i++) {
      String *current = row_name_vec[i];
      if (current != nullptr && *current == s) {
        return i;
      }
    }
    return -1;
  }

  /** The number of columns */
  size_t width() { return col_name_vec.size(); }

  /** The number of rows */
  size_t length() { return row_name_vec.size(); }
};