//#include "schema.h"
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

// void test1() {
//   Vec *cvec = new Cvec();
//   cvec->append('I');
//   cvec->append(' ');
//   cvec->append('O');
//   cvec->append('V');
//   cvec->append('e');

//   cvec->insert(2, 'L');
//   cvec->set(5, 'E');
//   // cvec->print_self();

//   String *i = new String("I");
//   String *love = new String("Love");
//   String *china = new String("China");
//   Vec *svec = new Svec();
//   svec->append(love);
//   svec->insert(0, i);
//   svec->append(i);
//   svec->set(2, china);
//   svec->print_self();
//   puts("");
//   Vec *colvec = new ColumnVec();
//   colvec->append(cvec);
//   colvec->append(svec);
//   colvec->insert(0, svec);
//   //vvec->print_self();
//   colvec->del(2);
//   china = new String("CHN");
//   svec->del(0);
//   svec->print_self();
//   puts("");
//   colvec->print_self();
//   //svec->print_self();
  
// }

void testColumn() {
  Column* col = new IntColumn(3,1,2,3);
  IntColumn* intCol = col->as_int();
  t_true(intCol->get(0) == 1);
}

// void testSchema() {
//   Schema* schema1 = new Schema();

// }

//void testSchema() { Schema *schema1 = new Schema(); }

int main(void) {
  //test1();
  testColumn();
}
