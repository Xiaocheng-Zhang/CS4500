#include "vec.h"

void test1() {
  vec *cvec_1 = new cvec();
  cvec_1->append('I');
  cvec_1->append(' ');
  cvec_1->append('O');
  cvec_1->append('V');
  cvec_1->append('e');

  cvec_1->insert(2, 'L');
  cvec_1->set(5, 'E');
  cvec_1->print_self();
}

void test2() {
  String *i = new String("I");
  String *love = new String("Love");
  String *china = new String("China");
  vec *svec_1 = new svec();
  svec_1->append(love);
  svec_1->insert(0, i);
  svec_1->append(i);
  svec_1->set(2, china);
  svec_1->print_self();
}

int main(void) {
  test1();
  test2();
}