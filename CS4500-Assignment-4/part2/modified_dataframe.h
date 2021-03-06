#include "../column.h"
#include "../object.h"
#include "../schema.h"
#include "../string.h"
#include "../vec.h"
#include <iostream>
#include <thread>
#include <stdarg.h>
#include <mutex>

class Compress : public Object {
public:
  Rower *r_;
  Row *row_;
  Compress(Row *row, Rower &r) : Object() {
    *r_ = r;
    row_ = row;
  }
};

void *thread_method(void *temp) { 
  Compress *c = (Compress*) temp;
  if (!c) {
    return 0;
  }
  c->r_->accept(*(c->row_));
  return nullptr; 
}
/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
public:
  Schema *schema_;
  ColumnVec *table_;

  /** Create a data frame with the same columns as the given df but with no rows
   * or rownmaes */
  DataFrame(DataFrame &df) {
    schema_ = df.schema_;
    table_ = df.table_;
  }

  /** Create a data frame from a schema and columns. All columns are created
   * empty. */
  DataFrame(Schema &schema) {
    schema_ = new Schema();
    schema_->type_vec = schema.type_vec->copy();
    schema_->col_name_vec = schema.col_name_vec->copy();
    schema_->row_name_vec = schema.row_name_vec->copy();
    table_ = new ColumnVec();
    for (int i = 0; i < schema_->type_vec->size_; i++) {
      char curr = schema_->type_vec->get_char(i);
      if (curr == 'I') {
        table_->append(new IntColumn());
      } else if (curr == 'S') {
        table_->append(new StringColumn());
      } else if (curr == 'B') {
        table_->append(new BoolColumn());
      } else if (curr == 'F') {
        table_->append(new FloatColumn());
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
    for (size_t i = 0; i < col->size(); i++) {
      schema_->add_row(nullptr);
    }
    table_->append(col);
  }

  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'I');
    Column *tmp = table_->get_Column(col);
    IntColumn *tmp2 = new IntColumn();
    tmp2->val_ = tmp->val_->copy();
    return tmp2->get(row);
  }
  bool get_bool(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'B');
    Column *tmp = table_->get_Column(col);
    BoolColumn *tmp2 = new BoolColumn();
    tmp2->val_ = tmp->val_->copy();
    return tmp2->get(row);
  }
  float get_float(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'F');
    Column *tmp = table_->get_Column(col);
    FloatColumn *tmp2 = new FloatColumn();
    tmp2->val_ = tmp->val_->copy();
    return tmp2->get(row);
  }
  String *get_string(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'S');
    Column *tmp = table_->get_Column(col);
    StringColumn *tmp2 = new StringColumn();
    tmp2->val_ = tmp->val_->copy();
    return tmp2->get(row);
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
    table_->list_[col]->val_->set(row, val);
  }
  void set(size_t col, size_t row, bool val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'B');
    table_->list_[col]->val_->set(row, val);
  }
  void set(size_t col, size_t row, float val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    table_->list_[col]->val_->set(row, val);
  }
  void set(size_t col, size_t row, String *val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(schema_->col_type(col) == 'S');
    table_->list_[col]->val_->set(row, val);
  }

  /** Set the fields of the given row object with values from the columns at
   * the given offset.  If the row is not form the same schema as the
   * dataframe, results are undefined.
   */
  void fill_row(size_t idx, Row &row) {
    assert(idx >= 0);
    assert(row.type_vec->equals(schema_->type_vec));
    for (size_t i = 0; i < schema_->width(); i++) {
      char type = schema_->col_type(i);
      if (type == 'I') {
        table_->list_[i]->val_->set(idx, row.get_int(i));
      } else if (type == 'B') {
        table_->list_[i]->val_->set(idx, row.get_bool(i));
      } else if (type == 'F') {
        table_->list_[i]->val_->set(idx, row.get_float(i));
      } else if (type == 'S') {
        table_->list_[i]->val_->set(idx, row.get_string(i));
      }
    }
  }

  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row &row) {
    assert(row.type_vec->equals(schema_->type_vec));
    for (size_t i = 0; i < schema_->width(); i++) {
      char type = schema_->col_type(i);
      if (type == 'I') {
        table_->list_[i]->val_->append(row.get_int(i));
      } else if (type == 'B') {
        table_->list_[i]->val_->append(row.get_bool(i));
      } else if (type == 'F') {
        table_->list_[i]->val_->append(row.get_float(i));
      } else if (type == 'S') {
        table_->list_[i]->val_->append(row.get_string(i));
      }
    }
  }

  /** The number of rows in the dataframe. */
  size_t nrows() { return schema_->length(); }

  /** The number of columns in the dataframe.*/
  size_t ncols() { return schema_->width(); }

  Row *track_row(size_t idx) {
    Row *temp = new Row(*schema_);
    for (size_t col = 0; col < ncols(); col++) {
      char type = schema_->col_type(col);
      if (type == 'I') {
        temp->set(col, table_->get_Column(col)->as_int()->get(idx));
      } else if (type == 'B') {
        temp->set(col, table_->get_Column(col)->as_bool()->get(idx));
      } else if (type == 'F') {
        temp->set(col, table_->get_Column(col)->as_float()->get(idx));
      } else if (type == 'S') {
        temp->set(col, table_->get_Column(col)->as_string()->get(idx));
      }
    }
    return temp;
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

  /** Print the dataframe in SoR format to standard output. */
  void print() {
    schema_->col_name_vec->print_self();
    for (size_t row = 0; row < nrows(); row++) {
      for (size_t col = 0; col < ncols(); col++) {
        char type = schema_->type_vec->get_char(col);
        if (type == 'I') {
          std::cout << this->get_int(col, row) << std::endl;
        } else if (type == 'B') {
          std::cout << this->get_bool(col, row) << std::endl;
        } else if (type == 'F') {
          std::cout << this->get_float(col, row) << std::endl;
        } else if (type == 'S') {
          std::cout << this->get_string(col, row)->c_str() << std::endl;
        }
      }
    }
  }
  /** This method clones the Rower and executes the map in parallel. Join is
   * used at the end to merge the results. */
  void pmap(Rower &r) {
    size_t thread_num = nrows();
    Rower **rower_array = new Rower *[thread_num];
    Rower *rower = new Rower();
    rower = &r;
    for (size_t i = 0; i < thread_num; i++) {
      rower_array[i] = rower;
    }
    pthread_t threads[thread_num];

    for (int i = 0; i < thread_num; ++i) {
      void *c = (void *) new Compress(track_row(i), rower[i]);
      pthread_create(&threads[i], 0, thread_method, c);
    }
    
    for (int i = 0; i < thread_num; ++i) {
      pthread_join(threads[i], 0);
    }
  }
};

