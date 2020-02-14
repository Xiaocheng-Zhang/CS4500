#include "vec.h"
#include "column.h"

void FAIL() { exit(1); }
void OK(const char *m) { std::cout << m << "\n"; }
void t_true(bool p) {
  if (!p)
    FAIL();
}
void t_false(bool p) {
  if (p)
    FAIL();
}

void test1() {
  Vec *cvec = new Cvec();
  cvec->append('I');
  cvec->append(' ');
  cvec->append('O');
  cvec->append('V');
  cvec->append('e');

  cvec->insert(2, 'L');
  cvec->set(5, 'E');
  // cvec->print_self();

  String *i = new String("I");
  String *love = new String("Love");
  String *china = new String("China");
  Vec *svec = new Svec();
  svec->append(love);
  svec->insert(0, i);
  svec->append(i);
  svec->set(2, china);
  svec->print_self();
  puts("");
  //vvec->print_self();
  china = new String("CHN");
  svec->del(0);
  svec->print_self();
  puts("");
  //svec->print_self();
  
}

void testIntColumn() {
  // test empty constructor
  Column* col_1 = new IntColumn();
  IntColumn* intCol_1 = col_1->as_int();
  t_true(intCol_1->size() == 0);
  
  // test variable argument constructor
  Column* col_2 = new IntColumn(3,1,2,3);
  IntColumn* intCol_2 = col_2->as_int();
  // test get method
  t_true(intCol_2->get(0) == 1 && intCol_2->get(1) == 2 && intCol_2->get(2) == 3);
  // test size method
  t_true(intCol_2->size() == 3);
  // test get_type method
  t_true(intCol_2->get_type() == 'I');
  // test set method
  intCol_2->set(0, 4);
  t_true(intCol_2->get(0) == 4);
  // test as_int method
  IntColumn* copy = intCol_2->as_int();
  t_true(copy->val_->equals(intCol_2->val_));
  OK("testIntColumn");
}

void testBoolColumn() {
  // test empty constructor
  Column* col_1 = new BoolColumn();
  BoolColumn* boolCol_1 = col_1->as_bool();
  t_true(boolCol_1->size() == 0);
  
  // test variable argument constructor
  Column* col_2 = new BoolColumn(3,true,false,false);
  BoolColumn* boolCol_2 = col_2->as_bool();
  // test get method
  t_true(boolCol_2->get(0) == true && boolCol_2->get(1) == false && boolCol_2->get(2) == false);
  // test size method
  t_true(boolCol_2->size() == 3);
  // test get_type method
  t_true(boolCol_2->get_type() == 'B');
  // test set method
  boolCol_2->set(0, false);
  t_true(boolCol_2->get(0) == false);
  // test as_int method
  BoolColumn* copy = boolCol_2->as_bool();
  t_true(copy->val_->equals(boolCol_2->val_));
  OK("testBoolColumn");
}

void testStringColumn() {
  // test empty constructor
  Column* col_1 = new StringColumn();
  StringColumn* stringCol_1 = col_1->as_string();
  t_true(stringCol_1->size() == 0);
  
  // test variable argument constructor
  Column* col_2 = new StringColumn(3,new String("Tian"),new String("Xia"),new String("Xiaocheng"));
  StringColumn* stringCol_2 = col_2->as_string();
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
  StringColumn* copy = stringCol_2->as_string();
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

// void testSchema() {
//   Schema* schema1 = new Schema();

// }

//void testSchema() { Schema *schema1 = new Schema(); }

int main(void) {
  //test1();
  testStringColumn();
  testBoolColumn();
  testIntColumn();
}
