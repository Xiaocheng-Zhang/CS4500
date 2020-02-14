#include "vec.h"
#include "column.h"
#include "schema.h"

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

void testSchema() {
  // test empty constructor
  Schema *schema1 = new Schema();
  t_true(schema1->type_vec->size_ == 0 && 
    schema1->col_name_vec->size_ == 0 && 
    schema1->row_name_vec->size_ == 0);

  // test type_check method
  t_true(schema1->type_check('I'));
  t_false(schema1->type_check('Q'));
  
  // test char pointer constructor
  Schema* schema2 = new Schema("IBSF");
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
  Schema* schema3 = new Schema(*schema2);
  // test if it can be mutated
  schema2->add_column('F', new String("mutation"));
  t_false(schema3->width() == schema2->width());
}

//void testSchema() { Schema *schema1 = new Schema(); }

int main(void) {
  //test1();
  testStringColumn();
  testBoolColumn();
  testIntColumn();
}
