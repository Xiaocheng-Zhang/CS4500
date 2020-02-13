#include "vec.h"

void test1() {
  Vec *cvec = new Cvec();
  cvec->append('I');
  cvec->append(' ');
  cvec->append('O');
  cvec->append('V');
  cvec->append('e');

  cvec->insert(2, 'L');
  cvec->set(5, 'E');
  //cvec->print_self();

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
  Vec *vvec = new Vvec();
  vvec->append(cvec);
  vvec->append(svec);
  vvec->insert(0, svec);
  //vvec->print_self();
  vvec->del(2);
  china = new String("CHN");
  svec->del(0);
  svec->print_self();
  puts("");
  vvec->print_self();
  //svec->print_self();
  
}

void test2() {
}


int main(void) {
  test1();
  test2();
}
