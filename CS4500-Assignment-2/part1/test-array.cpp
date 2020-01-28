#include "array.h"
#include "object.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Terminates program with error code
 *
 */
void FAIL() {
    exit(1);
}

/**
 * @brief Terminates program with success message
 *
 * @param m Message to be outputted
 */
void OK(const char* m) {
    printf(m);
}

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

void test_object1() {
    Object object1;
    Object object2 = object1.copy();
    t_true(object1.equals(object2));
    t_true(object1.hashcode() == object2.hashcode());
}

void test_array1() {
    Array array1;
    t_true(array1.size() == 0);
    Object object1;
    array1.append(object1);
    t_true(array1.size() == 1);
    t_true(array1.contains(object1));
    array1.remove(object1);
    t_false(array1.contains(object1));
}

void test_array2() {
    Array array1;
    Object object1;
    array1.append(object1);
    Object object2;
    array1.insert(object2, 0);
    t_true(object2.equals(array1.get(0)));
    array1.clear();
    t_true(array1.size() == 0);
}

int main()
{
    test_object1();
    test_array1();
    test_array2();
}
