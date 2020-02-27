#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"

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
  testDataframe();
  return 0;
}
