#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"

void testStringColumn() {
  // test empty constructor
  Column *col_1 = new StringColumn();
  StringColumn *stringCol_1 = col_1->as_string();
  t_true(stringCol_1->size() == 0);

  // test variable argument constructor
  Column *col_2 = new StringColumn(3, new String("Tian"), new String("Xia"),
                                   new String("Xiaocheng"));
  StringColumn *stringCol_2 = col_2->as_string();
  // test get method
  t_true(stringCol_2->get(0)->equals(new String("Tian")) &&
         stringCol_2->get(1)->equals(new String("Xia")) &&
         stringCol_2->get(2)->equals(new String("Xiaocheng")));
  // test size method
  t_true(stringCol_2->size() == 3);
  // test get_type method
  t_true(stringCol_2->get_type() == 'S');
  // test set method
  stringCol_2->set(0, new String("Zhang"));
  t_true(stringCol_2->get(0)->equals(new String("Zhang")));
  // test as_int method
  StringColumn *copy = stringCol_2->as_string();
  t_true(copy->val_->equals(stringCol_2->val_));
  Column *stringCol_3 = new StringColumn();
  stringCol_3->val_ = stringCol_2->val_->copy();
  t_true(stringCol_3->val_->equals(stringCol_2->val_));
  stringCol_2->val_->del(0);
  stringCol_2->val_->insert(0, new String("zhang"));
  t_false(stringCol_1->val_->equals(stringCol_2->val_));
  t_false(stringCol_3->val_->equals(stringCol_2->val_));
  OK("testStringColumn");
}

int main(void) {
  testStringColumn();
  return 0;
}