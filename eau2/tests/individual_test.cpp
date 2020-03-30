#include "../src/dataframe.h"
#include "../src/column.h"
#include "../src/helper.h"

void initialize() {
  Schema *schema;
  DataFrame *df;
  schema = new Schema();
  df = new DataFrame(*schema);

  IntColumn *int_col = new IntColumn();
  FloatColumn *float_col = new FloatColumn();
  BoolColumn *bool_col = new BoolColumn();
  StringColumn *string_col = new StringColumn();
  for (int i = 0; i < 50000; i++) {
    int_col->push_back(i);
    float_col->push_back(float(i));
    bool_col->push_back(true);
    string_col->push_back(new String("test String"));
  }

  df->add_column(int_col, new String("int_col"));
  df->add_column(float_col, new String("float_col"));
  df->add_column(bool_col, new String("bool_col"));
  df->add_column(string_col, new String("string_col"));
  puts("=======dataframe initialized 100,000 rows =======");
}

void testIntColumn() {
  // test empty constructor
  Column *col_1 = new IntColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new IntColumn(3, 1, 2, 3);
  // test get method
  t_true(col_2->get_int(0) == 1 && col_2->get_int(1) == 2 &&
         col_2->get_int(2) == 3);
  // test size method
  t_true(col_2->size() == 3);
  // test get_type method
  t_true(col_2->get_type() == 'I');
  // test set method
  col_2->set(0, 4);
  t_true(col_2->get_int(0) == 4);
  OK("testIntColumn");
}

void testBoolColumn() {
  // test empty constructor
  Column *col_1 = new BoolColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new BoolColumn(3, true, false, false);
  // test get method
  t_true(col_2->get_bool(0) == true && col_2->get_bool(1) == false &&
         col_2->get_bool(2) == false);
  // test size method
  t_true(col_2->size() == 3);
  // test get_type method
  t_true(col_2->get_type() == 'B');
  // test set method
  col_2->set(0, false);
  t_true(col_2->get_bool(0) == false);
  OK("testBoolColumn");
}

void testStringColumn() {
  // test empty constructor
  Column *col_1 = new StringColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new StringColumn(3, new String("Tian"), new String("Xia"),
                                   new String("Xiaocheng"));
  // test get method
  t_true(col_2->get_string(0)->equals(new String("Tian")) &&
         col_2->get_string(1)->equals(new String("Xia")) &&
         col_2->get_string(2)->equals(new String("Xiaocheng")));
  // test size method
  t_true(col_2->size() == 3);
  // test get_type method
  t_true(col_2->get_type() == 'S');
  // test set method
  col_2->set(0, new String("Zhang"));
  t_true(col_2->get_string(0)->equals(new String("Zhang")));
  OK("testStringColumn");
}

int main(void) {
  testIntColumn();
  testBoolColumn();
  testStringColumn();

  
}
