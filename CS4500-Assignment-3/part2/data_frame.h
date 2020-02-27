#pragma once

#include <iostream>
#include <object.h>
#include <vector>

/**
 * Implementors might want to treat T as Object so that
 * a DataColumn can accept all SoR which extended from Object.
 * A DataColumn is a column in DataFrame.
 * User can get value in this column by value's index.
 * A DataColumn should have a column symbol.
 * A column symbol should be char*.
 * If user did not provide a valid symbol for current column,
 * this column symbol will be signed as its index (char* version) automatically.
 * eg. "1" "2" "3" "Integer"
 * One column can only accept one type of value:
 * DataColumn<String>, DataColumn<Int>, DataColumn<Float>...
 * User cannot add Int value into String column.
 */
template <typename T> class DataColumn : public Object {
public:
  /**
   * Inset the value into this column. Implementors can make other insert
   * methods which accept column symbols.
   * @param index index that used to find the value.
   * @param value value that needed to be setted.
   */
  void insert(size_t index, T value);

  /**
   * Get the value by using column's index.
   * @param index index that used to find the value.
   * @return return T which is the dataType saved in this column.
   */
  T get_by_index(size_t index);

  /**
   * Reset the column symbol for this DataColumn.
   * @param name name that user want to use.
   */
  void reset_column_sym(char *name);
};

/**
 * Implementors might want to treat T as Object so that
 * a DataColumn can accept all SoR which extended from Object.
 * (one choice) DataFrame can have a DataColumn saved row symbols.
 * The same with DataColumn, row symbols can be setted mannually or
 * automatically.
 */
template <typename T> class DataFrame : public Object {
public:
  /**
   * Fields that implementors might need:
   * vector<DataColumn<T *> *> *data_;
   * size_t row_num_;
   * size_t column_num_;
   */

  /**
   * Constructor that implementors might need:
   * DataFrame (DataColumn<T> *column, ...) {
   * }
   */

  /**
   * Get value by its coordinate.
   * @param row row index.
   * @param col col index.
   */
  T get_by_coordinate(size_t row, size_t col);

  /**
   * Get value by its row symbol.
   * @param row_sym row symbol
   * @param column_sym column_sym
   * @return return T as its dataType
   */
  T get_by_coordinate_sym(char *row_sym, char *column_sym);

  /**
   * get total row number.
   * @return number of rows.
   */
  size_t nrow();

  /**
   * get total col number.
   * @return number of cols.
   */
  size_t ncol();

  /***
   * Change all value in this DataFrame into bool.
   * if there is a empty cell with nullptr,
   * it will be replaced by true.
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> isnull();

  /***
   * Change all value in this DataFrame into bool.
   * if there is a empty cell with nullptr,
   * it will be replaced by false.
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> notnull();

  /***
   * drop all rows that contains one or more null
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> dropna();

  /***
   * inset one column at a given index
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> insert(size_t index, T column_name, DataColumn<T> column);

  /***
   * drop the column at a given index
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> drop_by_index(size_t index);

  /***
   * drop the column given that column name
   * @return new DataFrame that saved those info.
   */
  DataFrame<T> drop_by_column_sym(char *column_sym);

  /***
   * Get the list of data type 
   * @return the vector of data type.
   */
  vector<T> dtypes();
};
