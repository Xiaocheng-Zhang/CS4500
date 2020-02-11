
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
  virtual IntColumn* as_int()
  virtual BoolColumn*  as_bool()
  virtual FloatColumn* as_float()
  virtual StringColumn* as_string()
 
  /** Type appropriate push_back methods. Calling the wrong method is
    * undefined behavior. **/
  virtual void push_back(int val)
  virtual void push_back(bool val)
  virtual void push_back(float val)
  virtual void push_back(String* val)
 
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
  IntColumn()
  IntColumn(int n, ...)
  int get(size_t idx)
  IntColumn* as_int()
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val)
  size_t size()
};
 
// Other primitive column classes similar...
 
/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
 public:
  StringColumn()
  StringColumn(int n, ...)
  StringColumn* as_string()
  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx)
  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val)
  size_t size()
};
 