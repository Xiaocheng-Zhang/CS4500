#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"

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

int main(void) {
  testRow();
  return 0;
}