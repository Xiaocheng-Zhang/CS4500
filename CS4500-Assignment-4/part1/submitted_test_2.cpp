#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"
void testBoolColumn() {
  // test empty constructor
  Column *col_1 = new BoolColumn();
  BoolColumn *boolCol_1 = col_1->as_bool();
  t_true(boolCol_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new BoolColumn(3, true, false, false);
  BoolColumn *boolCol_2 = col_2->as_bool();
  // test get method
  t_true(boolCol_2->get(0) == true && boolCol_2->get(1) == false &&
         boolCol_2->get(2) == false);
  // test size method
  t_true(boolCol_2->size() == 3);
  // test get_type method
  t_true(boolCol_2->get_type() == 'B');
  // test set method
  boolCol_2->set(0, false);
  t_true(boolCol_2->get(0) == false);
  // test as_int method
  BoolColumn *copy = boolCol_2->as_bool();
  t_true(copy->val_->equals(boolCol_2->val_));
  OK("testBoolColumn");
}

int main(void) {
  testBoolColumn();
  return 0;
}