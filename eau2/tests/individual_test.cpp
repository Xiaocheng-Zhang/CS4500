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

void testSchema() {
  // test empty constructor
  Schema *schema1 = new Schema();
  t_true(schema1->clone_type().size() == 0 && schema1->clone_type().size() == 0 &&
         schema1->clone_row_name().size() == 0);

  // test type_check method
  t_true(schema1->type_check('I'));
  t_false(schema1->type_check('Q'));

  // test char pointer constructor
  Schema *schema2 = new Schema("IBSF");
  t_true(schema2->type_vec->get_char(0) == 'I' &&
         schema2->type_vec->get_char(1) == 'B' &&
         schema2->type_vec->get_char(2) == 'S' &&
         schema2->type_vec->get_char(3) == 'F');

  // test adding a column with nullptr name
  schema2->add_column('I', nullptr);
  t_true(schema2->type_vec->get_char(4) == 'I');
  t_true(schema2->col_name_vec->get_String(4) == nullptr);
  // test adding a column with a non nullptr name
  schema2->add_column('B', new String("Tian"));
  t_true(schema2->type_vec->get_char(5) == 'B');
  t_true(schema2->col_name_vec->get_String(5)->equals(new String("Tian")));
  // test adding a row with nullptr name
  schema2->add_row(nullptr);
  t_true(schema2->row_name_vec->get_String(0) == nullptr);
  // test adding a row with a non nullptr name
  schema2->add_row(new String("Xia"));
  t_true(schema2->row_name_vec->get_String(1)->equals(new String("Xia")));
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

  // test copying constructor
  Schema *schema3 = new Schema(*schema2);
  // test if it can be mutated
  schema2->add_column('F', new String("mutation"));
  t_false(schema3->width() == schema2->width());
  OK("testSchema");
}

void testRow() {
  // construct a schema to be passeed into row
  Schema *schema = new Schema("IBSF");
  schema->add_column('B', new String("Tian"));
  // test row constructor
  Row *row = new Row(*schema);
  t_true(row->size_ == 5);
  t_true(row->index_ == 0);
  t_true(row->type_vec->equals(schema->type_vec));
  // t_true(sizeof(row->(buffer_array)) == 5);

  // test if it will be mutated if the schema is changed
  schema->add_column('F', new String("Xia"));
  t_true(row->size_ == 5);
  t_false(row->type_vec->equals(schema->type_vec));
  // t_true(sizeof(row->(buffer_array)) == 5);
  // test set and get method
  // set initial value
  row->set(0, 9);
  row->set(1, false);
  row->set(2, new String("Zhang"));
  row->set(3, float(1.23));
  t_true(row->get_int(0) == 9);
  t_true(row->get_bool(1) == false);
  t_true(row->get_string(2)->equals(new String("Zhang")));
  t_true(row->get_float(3) == float(1.23));
  // change values
  row->set(0, 8);
  t_true(row->get_int(0) == 8);

  // test set idx and get idx methods
  row->set_idx(4);
  t_true(row->get_idx() == 4);
  // test width method
  t_true(row->width() == 5);
  // test col_type method
  t_true(row->col_type(4) == 'B');
  Fielder *testFielder = new TestFielder();
  row->visit(0, *testFielder);
  OK("testRow");
}

void testDataframe() {
  // prepare schema for df
  Schema *schema = new Schema("IBSF");
  // using non empty schema to construct df, check constructor
  DataFrame *df = new DataFrame(*schema);

 
  t_true(df->schema_->col_type(0) == 'I' &&
         df->schema_->col_type(1) == 'B' &&
         df->schema_->col_type(2) == 'S' &&
         df->schema_->col_type(3) == 'F');
  // check the df schema wont be mutated
  schema->add_column('B', new String("Tian"));
  t_false(df->schema_->type_vec->equals(schema->type_vec));
  // test get schema method
  t_false(df->get_schema().type_vec->equals(schema->type_vec));
  // using an empty schema to construct df, check constructor
  Schema *schema2 = new Schema();
  DataFrame *df2 = new DataFrame(*schema2);
  // test add column method
  Column *col1 = new IntColumn(3, 1, 2, 3);
  Column *col2 = new StringColumn(3, new String("Tian"), new String("Xia"),
                                  new String("Zhang"));
  df2->add_column(col1, new String("Integer one"));
  df2->add_column(col2, new String("String one"));
  t_true(df2->schema_->col_name(0)->equals(new String("Integer one")));
  t_true(df2->schema_->col_name(1)->equals(new String("String one")));
  // test get method
  // df2->schema_->type_vec->print_self();
  // df2->table_->get_Column(0)->val_->print_self();
  // df2->table_->get_Column(1)->val_->print_self();
  t_true(df2->get_int(0, 1) == 2);
  t_true(df2->get_string(1, 1)->equals(new String("Xia")));
  // puts("here");
  // test get column method
  t_true(df2->get_col(*(new String("String one"))) == 1);
  t_true(df2->get_col(*(new String("Xiaocheng"))) == -1);
  // test set method
  df2->set(0, 1, 5);
  df2->set(1, 1, new String("Xiaocheng"));
  t_true(df2->get_int(0, 1) == 5);
  t_true(df2->get_string(1, 1)->equals(new String("Xiaocheng")));

  // test fill row method
  Row *row = new Row(df2->get_schema());
  row->set(0, 4);
  row->set(1, new String("new"));
  df2->fill_row(1, *row);
  t_true(df2->get_int(0, 1) == 4);
  t_true(df2->get_string(1, 1)->equals(new String("new")));
  // change row one element to see if df will be mutated
  row->set(0, 9);
  t_true(df2->get_int(0, 1) == 4);
  // test add row method, the row now is (9, "new")
  df2->add_row(*row);
  t_true(df2->get_int(0, 3) == 9);
  t_true(df2->get_string(1, 3)->equals(new String("new")));
  OK("testDataframe");
}

int main(void) {
  testIntColumn();
  testBoolColumn();
  testStringColumn();

  testSchema();
  testRow();
  testDataframe();
}
