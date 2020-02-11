#pragma once
#include <iostream>
#include "object.h"

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
  virtual IntColumn *as_int() virtual BoolColumn *as_bool() virtual FloatColumn
      *as_float() virtual StringColumn *as_string()

      /** Type appropriate push_back methods. Calling the wrong method is
       * undefined behavior. **/
      virtual void push_back(int val) virtual void push_back(
          bool
              val) virtual void push_back(float
                                              val) virtual void push_back(String
                                                                              *val)

      /** Returns the number of elements in the column. */
      virtual size_t size()

      /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'.
      char get_type()
    };

    /*************************************************************************
     * IntColumn::
     * Holds int values.
     */
      class IntColumn : public Column {
  public:
    IntColumn() IntColumn(int n, ...) int get(size_t idx) IntColumn *as_int()
        /** Set value at idx. An out of bound idx is undefined.  */
        void set(size_t idx, int val) size_t size()
  };

  // Other primitive column classes similar...

  /*************************************************************************
   * StringColumn::
   * Holds string pointers. The strings are external.  Nullptr is a valid
   * value.
   */
  class StringColumn : public Column {
  public:
    StringColumn() StringColumn(int n, ...) StringColumn *as_string()
        /** Returns the string at idx; undefined on invalid idx.*/
        String *get(size_t idx)
        /** Out of bound idx is undefined. */
        void set(size_t idx, String *val) size_t size()
  };

  /*************************************************************************
   * Schema::
   * A schema is a description of the contents of a data frame, the schema
   * knows the number of columns and number of rows, the type of each column,
   * optionally columns and rows can be named by strings.
   * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
   */
  class Schema : public Object {
  public:
    /** Copying constructor */
    Schema(Schema &from)

        /** Create an empty schema **/
        Schema()

        /** Create a schema from a string of types. A string that contains
         * characters other than those identifying the four type results in
         * undefined behavior. The argument is external, a nullptr argument is
         * undefined. **/
        Schema(const char *types)

        /** Add a column of the given type and name (can be nullptr), name
         * is external. Names are expectd to be unique, duplicates result
         * in undefined behavior. */
        void add_column(char typ, String *name)

        /** Add a row with a name (possibly nullptr), name is external.  Names
         * are expectd to be unique, duplicates result in undefined behavior. */
        void add_row(String *name)

        /** Return name of row at idx; nullptr indicates no name. An idx >=
         * width is undefined. */
        String *row_name(size_t idx)

        /** Return name of column at idx; nullptr indicates no name given.
         *  An idx >= width is undefined.*/
        String *col_name(size_t idx)

        /** Return type of column at idx. An idx >= width is undefined. */
        char col_type(size_t idx)

        /** Given a column name return its index, or -1. */
        int col_idx(const char *name)

        /** Given a row name return its index, or -1. */
        int row_idx(const char *name)

        /** The number of columns */
        size_t width()

        /** The number of rows */
        size_t length()
  };

  /*****************************************************************************
   * Fielder::
   * A field vistor invoked by Row.
   */
  class Fielder : public Object {
  public:
    /** Called before visiting a row, the argument is the row offset in the
      dataframe. */
    virtual void start(size_t r)

        /** Called for fields of the argument's type with the value of the
           field. */
        virtual void accept(bool b) virtual void accept(
            float f) virtual void accept(int i) virtual void accept(String *s)

        /** Called when all fields have been seen. */
        virtual void done()
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
    Row(Schema &scm)

        /** Setters: set the given column with the given value. Setting a column
         * with a value of the wrong type is undefined. */
        void set(size_t col, int val) void set(size_t col,
                                               float val) void set(size_t col,
                                                                   bool val)
        /** The string is external. */
        void set(size_t col, String *val)

        /** Set/get the index of this row (ie. its position in the dataframe.
         * This is only used for informational purposes, unused otherwise */
        void set_idx(size_t idx) size_t get_idx()

        /** Getters: get the value at the given column. If the column is not
         * of the requested type, the result is undefined. */
        int get_int(size_t col) bool get_bool(size_t col) float get_float(
            size_t col) String *get_string(size_t col)

        /** Number of fields in the row. */
        size_t width()

        /** Type of the field at the given position. An idx >= width is
           undefined. */
        char col_type(size_t idx)

        /** Given a Fielder, visit every field of this row. The first argument
         * is index of the row in the dataframe.
         * Calling this method before the row's fields have been set is
         * undefined. */
        void visit(size_t idx, Fielder &f)
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
    virtual bool accept(Row &r)

        /** Once traversal of the data frame is complete the rowers that were
            split off will be joined.  There will be one join per split. The
            original object will be the last to be called join on. The join
           method is reponsible for cleaning up memory. */
        void join_delete(Rower *other)
  };

  /****************************************************************************
   * DataFrame::
   *
   * A DataFrame is table composed of columns of equal length. Each column
   * holds values of the same type (I, S, B, F). A dataframe has a schema that
   * describes it.
   */
  class DataFrame : public Object {
  public:
    /** Create a data frame with the same columns as the given df but with no
     * rows or rownmaes */
    DataFrame(DataFrame &df)

        /** Create a data frame from a schema and columns. All columns are
         * created empty. */
        DataFrame(Schema &schema)

        /** Returns the dataframe's schema. Modifying the schema after a
         * dataframe has been created in undefined. */
        Schema &get_schema()

        /** Adds a column this dataframe, updates the schema, the new column
         * is external, and appears as the last column of the dataframe, the
         * name is optional and external. A nullptr colum is undefined. */
        void add_column(Column *col, String *name)

        /** Return the value at the given column and row. Accessing rows or
         *  columns out of bounds, or request the wrong type is undefined.*/
        int get_int(size_t col, size_t row) bool get_bool(
            size_t col, size_t row) float get_float(size_t col, size_t row)
            String *get_string(size_t col, size_t row)

        /** Return the offset of the given column name or -1 if no such col. */
        int get_col(String &col)

        /** Return the offset of the given row name or -1 if no such row. */
        int get_row(String &col)

        /** Set the value at the given column and row to the given value.
         * If the column is not  of the right type or the indices are out of
         * bound, the result is undefined. */
        void set(size_t col, size_t row, int val) void set(
            size_t col, size_t row,
            bool val) void set(size_t col, size_t row,
                               float val) void set(size_t col, size_t row,
                                                   String *val)

        /** Set the fields of the given row object with values from the columns
         * at the given offset.  If the row is not form the same schema as the
         * dataframe, results are undefined.
         */
        void fill_row(size_t idx, Row &row)

        /** Add a row at the end of this dataframe. The row is expected to have
         *  the right schema and be filled with values, otherwise undedined.  */
        void add_row(Row &row)

        /** The number of rows in the dataframe. */
        size_t nrows()

        /** The number of columns in the dataframe.*/
        size_t ncols()

        /** Visit rows in order */
        void map(Rower &r)

        /** Create a new dataframe, constructed from rows for which the given
         * Rower returned true from its accept method. */
        DataFrame *filter(Rower &r)

        /** Print the dataframe in SoR format to standard output. */
        void print()
  };