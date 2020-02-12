/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class Column : public Object {
 public:
  size_t size;


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
    return size;
  }
 
  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  virtual char get_type();
};
 
/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
 public:
  IntColumn();
  IntColumn(int n, ...);
  int get(size_t idx);
  IntColumn* as_int() {
    return this;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val);
  size_t size() {
    return size;
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
  BoolColumn();
  BoolColumn(bool n, ...);
  bool get(size_t idx);
  BoolColumn* as_bool() {
    return this;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, bool val);
  size_t size() {
    return size;
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
  FloatColumn();
  FloatColumn(float n, ...);
  float get(size_t idx);
  FloatColumn* as_float() {
    return this;
  }
  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, float val);
  size_t size() {
    return size;
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
  StringColumn()
  StringColumn(int n, ...)
  StringColumn* as_string()
  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx)
  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val)
  size_t size() {
    return size;
  }
  char get_type() {
    return 'S';
  }
};
