#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "node.h"
#include "object.h"
#include "string.h"

// Helper function to print out testing messages
void FAIL() { exit(1); }
void OK(const char *m) { printf("Passed: %s\n", m); }
void t_true(bool p) {
  if (!p)
    FAIL();
}
void t_false(bool p) {
  if (p)
    FAIL();
}

// Helper fucntion to cast object to String type
String *cast_string(Object *object) { return dynamic_cast<String *>(object); }

// Some predefined instances, includes String, Object, Map and Node.
String *s1 = new String("A");
String *s2 = new String("B");
String *s3 = new String("C");

Object *o1 = new Object();
Object *o2 = new Object();
Object *o3 = new Object();

Node *n1 = new Node(s1, o1);
Node *n2 = new Node(s2, o2);
Node *n3 = new Node(s3, o3);

Node *n4 = new Node(o1, s1);
Node *n5 = new Node(o2, s2);
Node *n6 = new Node(o3, s3);

Map *m1 = new Map();

// Test to check addElement
void test1() {
  String *o1 = new String("Test");
  String *o2 = new String("Value");
  Node *n1 = new Node(o1, o2);
  Map *m1 = new Map();
  m1->addElement(s1, o1);
}

// Tests to check node Constructor
void test2() {
  String *o1 = new String("Test");
  String *o2 = new String("Value");
  Node *n1 = new Node(o1, o2);
  Node *n2 = new Node();
}

// Tests Map Functions
void testAddElem() {
  Map *m1 = new Map();
  m1->addElement(s1, o1);
  m1->addElement(s2, o2);
  m1->addElement(s3, o3);
  t_true(m1->len_ == 3);
  t_true(m1->isKeyIn(s1) == 1);
  t_true(m1->isKeyIn(s2) == 1);
  t_true(m1->isKeyIn(s3) == 1);
}

// Tests to check removeElement functionality
void testRemoveElem() {
  Map *m1 = new Map();
  m1->addElement(s1, o1);
  m1->addElement(s2, o2);
  m1->addElement(s3, o3);
  t_true(m1->len_ == 3);
  m1->removeElement(s1);
  t_true(m1->len_ == 2);
  t_true(m1->isKeyIn(s1) == 0);
  t_true(m1->isKeyIn(s2) == 1);
  t_true(m1->isKeyIn(s3) == 1);
}

// Tests to check getValue functionality
void testGetValue() {
  Map *m1 = new Map();
  m1->addElement(s1, o1);
  m1->addElement(s2, o2);
  m1->addElement(s3, o3);
  t_true(m1->getValue(s1) == o1);
  t_true(m1->getValue(s2) == o2);
  t_true(m1->getValue(s3) == o3);
}


// --------------------------------------------------------------
// The tests above this line is provided by management team.
// All the tests below is created by implementers.
// --------------------------------------------------------------


// To test Map's basic functionality of put, getKeyArray and getLength.
void none_spec_test1() {
  String *a = new String("key_1");
  String *av = new String("val_1");
  Map *test_map = new Map();  

  t_true(test_map->getLength() == 0);
  test_map->addElement(a, av);
  t_true(test_map->getLength() == 1);

  Object **keys = test_map->key_array();
  //keys[0]->print();
  t_true(a->equals(keys[0]));
  OK("none_spec_test1");
}


// Adding Strings into Map multiple times to check if the addElement is working well.
// Also ensured isKeyIn functionality.
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
  test_map->addElement(a, av);
  test_map->addElement(b, bv);
  test_map->addElement(c, cv);
  test_map->addElement(d, dv);
  test_map->addElement(a, av);
  t_true(test_map->getLength() == 4);
  t_true(test_map->isKeyIn(a));
  test_map->addElement(dv, d);
  test_map->addElement(cv, c);
  t_true(test_map->getLength() == 6);
  OK("none_spec_test2");
}

// More advanced test for Hashmap.
// It involves addElement and equals functions.
// Two Hashmap should be equivelent if they contains the same pairs of key and value.
// no matter what sequence those pairs are added.
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
  test_map->addElement(a, av);
  test_map->addElement(b, bv);
  test_map->addElement(c, cv);
  test_map->addElement(d, dv);
  Map *test_map2 = new Map();
  test_map2->addElement(b, bv);
  test_map2->addElement(c, cv);
  test_map2->addElement(a, av);
  test_map2->addElement(d, dv);
  t_true(test_map->equals(test_map2));
  OK("advance_none_spec_test");
}

// Main function
int main(){
  test1();
  test2();
  testAddElem();
  testRemoveElem();
  testGetValue();

  // --------------------------------------------------------------
  // The tests above this line is provided by management team.
  // All the tests below is created by implementers.
  // --------------------------------------------------------------


  none_spec_test1();
  none_spec_test2();
  advance_none_spec_test();
  puts("All tests in test-map.cpp Passed!");
}
