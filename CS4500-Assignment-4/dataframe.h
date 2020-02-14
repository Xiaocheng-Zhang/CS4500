#include "column.h"
#include "object.h"
#include "schema.h"
#include "string.h"
#include "vec.h"
#include <iostream>
#include <stdarg.h>

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
    schema_->type_vec = schema.type_vec;
    schema_->col_name_vec = schema.col_name_vec;
    schema_->row_name_vec = schema.row_name_vec;
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
    table_->append(col);
  }

  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'I');
    return table_->get_Column(col)->as_int()->get(row);
  }
  bool get_bool(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'B');
    return table_->get_Column(col)->as_bool()->get(row);
  }
  float get_float(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'F');
    return table_->get_Column(col)->as_float()->get(row);
  }
  String *get_string(size_t col, size_t row) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'S');
    return table_->get_Column(col)->as_string()->get(row);
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
    assert(table_->get_Column(col)->get_type() == 'I');
    table_->get_Column(col)->as_int()->set(row, val);
  }
  void set(size_t col, size_t row, bool val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'B');
    table_->get_Column(col)->as_bool()->set(row, val);
  }
  void set(size_t col, size_t row, float val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'F');
    table_->get_Column(col)->as_float()->set(row, val);
  }
  void set(size_t col, size_t row, String *val) {
    assert(col >= 0 && col < schema_->width());
    assert(row >= 0 && row < schema_->length());
    assert(table_->get_Column(col)->get_type() == 'S');
    table_->get_Column(col)->as_string()->set(row, val);
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
        IntColumn *temp = dynamic_cast<IntColumn *>(table_->get_Column(i));
        temp->set(idx, row.get_int(i));
        table_->set(i, temp);
      } else if (type == 'B') {
        BoolColumn *temp = dynamic_cast<BoolColumn *>(table_->get_Column(i));
        temp->set(idx, row.get_int(i));
        table_->set(i, temp);
      } else if (type == 'F') {
        FloatColumn *temp = dynamic_cast<FloatColumn *>(table_->get_Column(i));
        temp->set(idx, row.get_float(i));
        table_->set(i, temp);
      } else if (type == 'S') {
        StringColumn *temp =
            dynamic_cast<StringColumn *>(table_->get_Column(i));
        temp->set(idx, row.get_string(i));
        table_->set(i, temp);
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
        IntColumn *temp = dynamic_cast<IntColumn *>(table_->get_Column(i));
        temp->push_back(row.get_int(i));
        table_->set(i, temp);
      } else if (type == 'B') {
        BoolColumn *temp = dynamic_cast<BoolColumn *>(table_->get_Column(i));
        temp->push_back(row.get_bool(i));
        table_->set(i, temp);
      } else if (type == 'F') {
        FloatColumn *temp = dynamic_cast<FloatColumn *>(table_->get_Column(i));
        temp->push_back(row.get_float(i));
        table_->set(i, temp);
      } else if (type == 'S') {
        StringColumn *temp =
            dynamic_cast<StringColumn *>(table_->get_Column(i));
        temp->push_back(row.get_string(i));
        table_->set(i, temp);
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
  DataFrame *filter(Rower &r);

  /** Print the dataframe in SoR format to standard output. */
  void print();
};
