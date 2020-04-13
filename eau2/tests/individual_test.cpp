#include "../src/dataframe.h"
#include "../src/column.h"
#include "../src/helper.h"
#include "../src/row.h"

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

void testIntColumnConstructor() {
  // test empty constructor
  Column *col_1 = new IntColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new IntColumn(3, 1, 2, 3);
  OK("testIntColumnConstructor");
}

void testIntColumnGetterAndSetter() {
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
  OK("testIntColumnGetterAndSetter");
}

void testBoolColumnConstructor() {
  // test empty constructor
  Column *col_1 = new BoolColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new BoolColumn(3, true, false, false);
  OK("testBoolColumnConstructor");
}

void testBoolColumnSetterAndGetter() {
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
  OK("testBoolColumnSetterAndGetter");
}

void testStringColumnConstructor() {
  // test empty constructor
  Column *col_1 = new StringColumn();
  t_true(col_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new StringColumn(3, new String("Tian"), new String("Xia"),
                                   new String("Xiaocheng"));
  OK("testStringColumnConstructor");
}

void testStringColumnGetterAndSetter() {
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
  OK("testStringColumnGetterAndSetter");
}

void testSchema1() {
  // test empty constructor
  Schema *schema1 = new Schema();
  t_true(schema1->clone_type().size() == 0 && schema1->clone_col_name().size() == 0 &&
         schema1->clone_row_name().size() == 0);

  // test type_check method
  t_true(schema1->type_check('I'));
  t_false(schema1->type_check('Q'));

  OK("testSchema1");
}

void testSchema2() {
  // test char pointer constructor
  Schema *schema2 = new Schema("IBSF");
  t_true(schema2->clone_type()[0] == 'I' &&
         schema2->clone_type()[1] == 'B' &&
         schema2->clone_type()[2] == 'S' &&
         schema2->clone_type()[3] == 'F');

  // test adding a column with nullptr name
  schema2->add_column('I', nullptr);
  t_true(schema2->clone_type()[4] == 'I');
  t_true(schema2->clone_col_name()[4] == nullptr);
  // test adding a column with a non nullptr name
  schema2->add_column('B', new String("Tian"));
  t_true(schema2->clone_type()[5] == 'B');
  t_true(schema2->clone_col_name()[5]->equals(new String("Tian")));
  // test adding a row with nullptr name
  schema2->add_row(nullptr);
  t_true(schema2->clone_row_name()[0] == nullptr);
  // test adding a row with a non nullptr name
  schema2->add_row(new String("Xia"));
  t_true(schema2->clone_row_name()[1]->equals(new String("Xia")));
  // test row_name method
  t_true(schema2->row_name(1)->equals(new String("Xia")));
  // test col_name method
  t_true(schema2->col_name(5)->equals(new String("Tian")));
  // test col_type method
  t_true(schema2->col_type(5) == 'B');
  // test col_idx method
  t_true(schema2->col_idx("Tian") == 5);
  t_true(schema2->col_idx("Xiaocheng") == -1);
  // test row_idx method
  t_true(schema2->row_idx("Xia") == 1);
  t_true(schema2->col_idx("Zhang") == -1);
  // test width and length method
  t_true(schema2->width() == 6);
  t_true(schema2->length() == 2);
  OK("testSchema2");
}

void testSchema3() {
  Schema *schema2 = new Schema("IBSF");
  // test copying constructor
  Schema *schema3 = new Schema(*schema2);
  // test if it can be mutated
  schema2->add_column('F', new String("mutation"));
  t_false(schema3->width() == schema2->width());
  OK("testSchema3");
}

