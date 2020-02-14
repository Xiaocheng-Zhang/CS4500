#include "../column.h"
#include "dataframe.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"

void testIntColumn() {
  // test empty constructor
  Column *col_1 = new IntColumn();
  IntColumn *intCol_1 = col_1->as_int();
  t_true(intCol_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new IntColumn(3, 1, 2, 3);
  IntColumn *intCol_2 = col_2->as_int();
  // test get method
  t_true(intCol_2->get(0) == 1 && intCol_2->get(1) == 2 &&
         intCol_2->get(2) == 3);
  // test size method
  t_true(intCol_2->size() == 3);
  // test get_type method
  t_true(intCol_2->get_type() == 'I');
  // test set method
  intCol_2->set(0, 4);
  t_true(intCol_2->get(0) == 4);
  // test as_int method
  IntColumn *copy = intCol_2->as_int();
  t_true(copy->val_->equals(intCol_2->val_));
  OK("testIntColumn");
}

int main(void) {
    testIntColumn();
    return 0;
}