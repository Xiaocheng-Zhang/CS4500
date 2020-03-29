#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "column.h"
#include "kvstore.h"
#include "object.h"
#include "row.h"
#include "schema.h"
#include "string.h"

using namespace std;

class DataFrame : public Object {
private:
  Schema *schema_;
  vector<Column *> table_;

public:
  DataFrame(DataFrame &df) {
    schema_ = new Schema(df.get_schema());
    set_up_by_schema();
    for (size_t i = 0; i < schema_->width(); i++) {
      char type = schema_->col_type(i);
      for (size_t j = 0; j < schema_->length(); j++) {
        if (type == INTEGER_C) {
          set(i, j, df.get_int(j, i));
        } else if (type == STRING_C) {
          set(i, j, df.get_string(j, i));
        } else if (type == BOOL_C) {
          set(i, j, df.get_bool(j, i));
        } else if (type == FLOAT_C) {
          set(i, j, df.get_double(j, i));
        }
      }
    }
  }

  DataFrame(Schema &schema) {
    schema_ = new Schema(schema);
    set_up_by_schema();
  }

  ~DataFrame() { delete schema_; }

  void set_up_by_schema() {
    for (int i = 0; i < schema_->width(); i++) {
      char curr = schema_->col_type(i);
      if (curr == INTEGER_C) {
        table_.push_back(new IntColumn());
      } else if (curr == STRING_C) {
        table_.push_back(new StringColumn());
      } else if (curr == BOOL_C) {
        table_.push_back(new BoolColumn());
      } else if (curr == FLOAT_C) {
        table_.push_back(new FloatColumn());
      } else {
        std::cout << "The char other than I, B, S, F was detected, table "
                     "cannot be built"
                  << std::endl;
        exit(0);
      }
    }
  }

  /** Returns the dataframe's schema. Modifying the schema after a dataframe
   * has been created in undefined. */
  Schema &get_schema() { return *schema_; }

  /** Adds a column this dataframe, updates the schema, the new column
   * is external, and appears as the last column of the dataframe, the
   * name is optional and external. A nullptr colum is undefined. */
  void add_column(Column *col, String *name) {
    assert(col != nullptr);
    char type = col->get_type();
    schema_->add_column(type, name);
    size_t col_size = col->size();
    size_t row_num = schema_->length();
    if (col_size > row_num) {
      for (size_t i = 0; i < col_size - row_num; i++) {
        schema_->add_row(nullptr);
      }
    }
    table_.push_back(col);
  }

  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t row, size_t col) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'I');
    return table_[col]->get_int(row);
  }

  bool get_bool(size_t row, size_t col) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'B');
    return table_[col]->get_bool(row);
  }

  float get_double(size_t row, size_t col) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'F');
    return table_[col]->get_float(row);
  }

  String *get_string(size_t row, size_t col) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'S');
    return table_[col]->get_string(row);
  }

  /** Return the offset of the given column name or -1 if no such col. */
  int get_col(String &col) { return schema_->col_idx(col.c_str()); }

  /** Return the offset of the given row name or -1 if no such row. */
  int get_row(String &col) { return schema_->row_idx(col.c_str()); }

  /** Set the value at the given column and row to the given value.
   * If the column is not  of the right type or the indices are out of
   * bound, the result is undefined. */
  void set(size_t col, size_t row, int val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'I');
    table_[col]->set(row, val);
  }

  void set(size_t col, size_t row, bool val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'B');
    table_[col]->set(row, val);
  }

  void set(size_t col, size_t row, float val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'F');
    table_[col]->set(row, val);
  }

  void set(size_t col, size_t row, String *val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'S');
    table_[col]->set(row, val);
  }

  /** The number of rows in the dataframe. */
  size_t nrows() { return schema_->length(); }

  /** The number of columns in the dataframe.*/
  size_t ncols() { return schema_->width(); }

  /** Set the fields of the given row object with values from the columns at
   * the given offset.  If the row is not form the same schema as the
   * dataframe, results are undefined.
   */
  void fill_row(size_t idx, Row &row) {
    assert(idx >= 0);
    assert(row.check_schema(*schema_));
    for (size_t i = 0; i < schema_->width(); i++) {
      char type = schema_->col_type(i);
      if (type == INTEGER_C) {
        table_[i]->set(idx, row.get_int(i));
      } else if (type == BOOL_C) {
        table_[i]->set(idx, row.get_bool(i));
      } else if (type == FLOAT_C) {
        table_[i]->set(idx, row.get_float(i));
      } else if (type == STRING_C) {
        table_[i]->set(idx, row.get_string(i));
      }
    }
    schema_->add_row(nullptr);
  }

  Row *track_row(size_t idx) {
    // schema_->type_vec->print_self();
    Row *temp = new Row(*schema_);
    // std::cout<<idx<<"\n";
    for (size_t col = 0; col < ncols(); col++) {
      char type = schema_->col_type(col);

      if (type == INTEGER_C) {
        temp->set(col, table_[col]->get_int(idx));
      } else if (type == BOOL_C) {
        temp->set(col, table_[col]->get_bool(idx));
      } else if (type == FLOAT_C) {
        temp->set(col, table_[col]->get_float(idx));
      } else if (type == STRING_C) {
        temp->set(col, table_[col]->get_string(idx));
      }
    }
    return temp;
  }

  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row &row) {
    assert(row.check_schema(*schema_));
    for (size_t i = 0; i < schema_->width(); i++) {
      char type = schema_->col_type(i);
      if (type == INTEGER_C) {
        table_[i]->push_back(row.get_int(i));
      } else if (type == BOOL_C) {
        table_[i]->push_back(row.get_bool(i));
      } else if (type == FLOAT_C) {
        table_[i]->push_back(row.get_float(i));
      } else if (type == STRING_C) {
        table_[i]->push_back(row.get_string(i));
      }
    }
    schema_->add_row(nullptr);
  }

  /** Visit rows in order */
  void map(Rower &r) {
    for (size_t i = 0; i < nrows(); i++) {
      r.accept(*(track_row(i)));
    }
  }

  /** Create a new dataframe, constructed from rows for which the given Rower
   * returned true from its accept method. */
  DataFrame *filter(Rower &r) {
    DataFrame *temp = new DataFrame(*schema_);
    for (size_t i = 0; i < nrows(); i++) {
      Row *temp_row = track_row(i);
      if (r.accept(*temp_row)) {
        temp->add_row(*temp_row);
      }
    }
    return temp;
  }

  static Row *track_row_static(Schema *schema, vector<Column *> table,
                               size_t idx) {
    // schema_->type_vec->print_self();
    Row *temp = new Row(*schema);
    // std::cout<<idx<<"\n";
    for (size_t col = 0; col < schema->width(); col++) {
      char type = schema->col_type(col);
      if (type == INTEGER_C) {
        temp->set(col, table[col]->get_int(idx));
      } else if (type == BOOL_C) {
        temp->set(col, table[col]->get_bool(idx));
      } else if (type == FLOAT_C) {
        temp->set(col, table[col]->get_float(idx));
      } else if (type == STRING_C) {
        temp->set(col, table[col]->get_string(idx));
      }
    }
    return temp;
  }

  static void thread_method(Rower *r, vector<Column *> table, Schema *schema,
                            size_t start_idx, size_t end_idx) {
    for (size_t i = start_idx; i <= end_idx; i++) {
      r->accept(*(track_row_static(schema, table, i)));
    }
  }

  /** This method clones the Rower and executes the map in parallel. Join
  is
   * used at the end to merge the results. */
  void pmap(Rower &r) {
    size_t row_num = nrows();
    size_t split_num = 0;
    size_t thread_num = 0;
    if (row_num > 7) {
      thread_num = 7;
      split_num = row_num / thread_num;
    } else {
      split_num = 1;
      thread_num = row_num;
    }
    size_t offset = row_num - thread_num * split_num;
    // + 1 for offset
    // std::cout<<thread_num<<" "<<row_num<<" "<< split_num << " " <<
    // <<"\n";
    thread threads[thread_num + 1];
    Rower **rower_array = new Rower *[thread_num + 1];
    for (size_t i = 0; i <= thread_num; ++i) {
      size_t start_idx = i * split_num;
      size_t end_idx = 0;
      if (i != thread_num) {
        end_idx = (i + 1) * split_num - 1;
      } else {
        end_idx = start_idx + offset - 1;
      }

      rower_array[i] = dynamic_cast<Rower *>(r.clone());
      threads[i] = thread(thread_method, rower_array[i], table_, schema_,
                          start_idx, end_idx);
    }

    for (size_t i = 0; i <= thread_num; ++i) {
      threads[i].join();
      r.join_delete(rower_array[i]);
    }
    delete[] rower_array;
  }

  static DataFrame *fromArray(Key *key, KVStore<DataFrame *> *kv, size_t SZ,
                              double *vals) {
    Schema *schema = new Schema();
    for (size_t i = 0; i < SZ; i++) {
      schema->add_column('F', nullptr);
    }
    schema->add_row(nullptr);

    DataFrame *df = new DataFrame(*schema);
    Row *r = new Row(*schema);
    for (size_t i = 0; i < SZ; i++) {
      r->set(i, (float)vals[i]);
    }
    df->add_row(*r);
    kv->put(key, df);
    DataFrame *tmp = new DataFrame(*df);
    return tmp;
  }
};