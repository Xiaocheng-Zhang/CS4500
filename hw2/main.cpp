#include "object.h"  // Your file with the CwC declaration of Object
#include "string.h"  // Your file with the String class
#include "list.h"    // Your file with the two list classes
 
void FAIL() {   exit(1);    }
void OK(const char* m) { 
  printf("test%s passed\n", m);
  /** print m */ }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }
 
void test1() {
  String * s = new String("Hello");
  String * t = new String("World");
  String * u = s->concat(t);
  t_true(s->equals(s));
  t_false(s->equals(t));
  t_false(s->equals(u));
  OK("1");
}
 
void test2() {
  String * s = new String("Hello");
  String * t = new String("World");
  String * u = s->concat(t);
  SortedStrList * l = new SortedStrList();
  l->sorted_add(s);
  l->sorted_add(t);
  l->sorted_add(u);
  t_true(l->get(0)->equals(s));
  OK("2");
}
 
void test3() {
  String * s = new String("Hello");
  String * t = new String("World");
  String * u = s->concat(t);
  SortedStrList * l = new SortedStrList();
  l->sorted_add(s);
  l->sorted_add(t);
  l->sorted_add(u);
  SortedStrList * l2 = new SortedStrList();
  l2->sorted_add(s);
  l2->sorted_add(t);
  l2->sorted_add(u);
  t_true(l->equals(l2));
  t_true(l2->equals(l));
  t_true(l->hash() == l2->hash());
  OK("3");
}
 
void test4() {
  String * s = new String("Hello");
  String * t = new String("World");
  String * s2 = new String("Hello");
  String * t2 = new String("World");
  String * u = s->concat(t);
  SortedStrList * l = new SortedStrList();
  l->sorted_add(s);
  l->sorted_add(t);
  l->sorted_add(u);
  SortedStrList * l2 = new SortedStrList();
  SortedStrList * l3 = new SortedStrList();
  l3->sorted_add(s2);
  l3->sorted_add(t2);
  l3->sorted_add(u);
  l2->add_all(0,l);
  t_true(l->size() == l2->size());
  t_true(l->hash() == l3->hash());
  OK("4");
}

void test5() {
  String *s1 = new String("Shawn");
  String *s2 = new String("love");
  String *s3 = new String("CS4500");
  String *s4 = new String("CS4100");
  StrList *l1 = new StrList();
  StrList *l2 = new StrList();
  l1->push_back(s1);
  l2->push_back(s1);
  l1->push_back(s2);
  l2->push_back(s2);
  l1->push_back(s3);
  l2->push_back(s4);
  t_false(l1->equals(l2));
  t_false(l1->contains(s4));
  t_true(l2->contains(s4));
  t_false(l1->equals(l2));
  t_false(l1->hash() == l2->hash());
  OK("5");
}

void test6() {
  String *s1 = new String("Shawn");
  String *s2 = new String("love");
  String *s3 = new String("Math");
  SortedStrList *l1 = new SortedStrList();
  StrList *l2 = new StrList();
  l1->sorted_add(s1);
  l2->push_back(s1);
  l1->sorted_add(s2);
  l2->push_back(s2);
  l1->sorted_add(s3);
  l2->push_back(s3);
  t_true(l1->equals(l2));
  t_true(l1->hash() == l2->hash());
    for (int i = 0; i < l1->size(); i++) {
      //printf("%s\n", l1->get(i)->getValue());
    }
  OK("6");
}

void test7() {
  String *s1 = new String("Hello");
  String *s2 = new String("World");
  String *s3 = new String("HelloWorld");
  SortedStrList *l1 = new SortedStrList();
  l1->push_back(s1);
  l1->push_back(s2);
  l1->push_back(s3);
  l1->merge_sort(0, 2);
  SortedStrList *l2 = new SortedStrList();
  l2->sorted_add(s1);
  l2->sorted_add(s2);
  l2->sorted_add(s3);
  t_true(l1->equals(l2));
  t_true(l1->hash() == l2->hash());
  OK("7");
}

int main(void) {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  return 0;
}