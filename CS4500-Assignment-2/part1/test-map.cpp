#include "object.h"
#include "string.h"
#include "node.h"
#include "map.h"

#include <stdio.h>
#include <stdlib.h>

//Test to check addElement
void test1(){
  String* o1 = new String("Test");
  String* o2 = new String("Value");
  Node* n1 = new Node(o1, o2);
  Map* m1 = new Map();
  m1 -> addElement(n1);
}

//Tests to check node Constructor
void test2(){
  String* o1 = new String("Test");
  String* o2 = new String("Value");
  Node* n1 = new Node(o1, o2);
  Node* n2 = new Node();
}

void test3(){
  //Will test to check if a given value is in the map based on key

  //Will test to check the length of the map

  //Will check to test the equality of the map
}

/** everything in this block is created by implementor team*/
void FAIL() { exit(1); }
void OK(const char* m) { printf("test %s passed\n", m); }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }

void none_spec_test1() {
  String *a = new String("key_1");
  String *av = new String("val_1");
  Map *test_map = new Map();  

  t_true(test_map->size() == 0);
  test_map->put(a, av);
  t_true(test_map->size() == 1);

  Object **keys = test_map->key_array();
  //keys[0]->print();
  t_true(a->equals(keys[0]));
  OK("none_spec_test1");
}

void none_spec_test2() {
  String *a = new String("key_1");
  String *b = new String("key_2");
  String *c = new String("key_3");
  String *d = new String("key_4");
  String *av = new String("val_1");
  String *bv = new String("val_2");
  String *cv = new String("val_3");
  String *dv = new String("val_4");

  Map *test_map = new Map();
  test_map->put(a, av);
  test_map->put(b, bv);
  test_map->put(c, cv);
  test_map->put(d, dv);
  test_map->put(a, av);
  t_true(test_map->size() == 4);
  //t_true(test_map->capacity_ == 8);
  t_true(test_map->isKeyIn(a));
  test_map->put(dv, d);
  test_map->put(cv, c);
  t_true(test_map->size() == 6);
  OK("none_spec_test2");
}

void advance_none_spec_test() {
  String *a = new String("key_1");
  String *b = new String("key_2");
  String *c = new String("key_3");
  String *d = new String("key_4");
  String *av = new String("val_1");
  String *bv = new String("val_2");
  String *cv = new String("val_3");
  String *dv = new String("val_4");

  Map *test_map = new Map();
  test_map->put(a, av);
  test_map->put(b, bv);
  test_map->put(c, cv);
  test_map->put(d, dv);
  Map *test_map2 = new Map();
  test_map2->put(b, bv);
  test_map2->put(c, cv);
  test_map2->put(a, av);
  test_map2->put(d, dv);
  t_true(test_map->equals(test_map2));
  OK("advance_none_spec_test");
}
/** everything in this block is created by implementor team*/

int main(){
  test1();
  test2();
  none_spec_test1();
  none_spec_test2();
  advance_none_spec_test();
}
