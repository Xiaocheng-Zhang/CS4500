#include "array.h"
#include "object.h"
#include "string.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Terminates program with error code
 *
 */
void FAIL() { exit(1); }

/**
 * @brief Terminates program with success message
 *
 * @param m Message to be outputted
 */
void OK(const char *m) { printf("test: %s passed\n", m); }

/**
 * @brief Checks if condition true, fails otherwise
 *
 * @param p condition to be checked
 */
void t_true(bool p) {
  if (!p) {
    FAIL();
  }
}

/**
 * @brief Checks if condition false, fails otherwise
 *
 * @param p condition to be checked
 */
void t_false(bool p) {
  if (p) {
    FAIL();
  }
}

void test_array1() {
  Int_Array *array1 = new Int_Array();
  t_true(array1->size() == 0);
  int o1 = 10;
  array1->append(o1);
  t_true(array1->size() == 1);
  t_true(array1->contains(o1));
  array1->remove(0);
  t_false(array1->contains(o1));
}

void test_array2() {
  Int_Array *array1 = new Int_Array();
  int o1 = 10;
  array1->append(o1);
  int o2 = 20;
  array1->insert(o2, 0);
  t_true(o2 == array1->get(0));
  array1->clear();
  t_true(array1->size() == 0);
}

/** everything in this block is created by implementor team*/
void none_spec_test1() {
  String *a = new String("Hellow");
  Array *array = new Array();
  t_true(array->size() == 0);
  array->append(a);
  t_true(array->size() == 1);

  int i = 10;
  Int_Array *int_array = new Int_Array();
  int_array->append(i);
  t_true(array->get(0) == 10);
  OK("none_spec_test1");
}

void none_spec_test2() {
  String *a = new String("Hellow");
  String *b = new String("World");
  String *c = new String("Xiaocheng");
  String *d = new String("TianXia");
  Array *array = new Array();
  array->append(a);
  array->append(b);
  array->append(c);
  array->append(d);
  t_true(array->get(3)->equals(d));
  t_true(array->get(0)->equals(a));
  t_true(array->get(2)->equals(c));
  OK("none_spec_test2");
}

void advance_none_spec_test() {
  String *a = new String("Hellow");
  String *b = new String("World");
  String *c = new String("Xiaocheng");
  String *d = new String("TianXia");
  Array *array = new Array();
  array->append(a);
  array->append(b);
  array->append(c);
  array->append(d);
  t_true(array->get(3)->equals(d));
  t_true(array->get(0)->equals(a));
  t_true(array->get(2)->equals(c));
  array->remove(0);
  t_true(array->get(0)->equals(b));
  OK("advance_none_spec_test");
}
/** everything in this block is created by implementor team*/

int main() {
  test_array1();
  test_array2();
  none_spec_test1();
  none_spec_test2();
  advance_none_spec_test();
  return 0;
}
