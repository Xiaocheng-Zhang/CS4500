#include "array.h"
#include "int_array.h"
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

void test_array1() {
    Int_Array* array1 = new Int_Array();
    t_true(array1->size() == 0);
    int o1 = 10;
    array1->append(o1);
    t_true(array1->size() == 1);
    t_true(array1->contains(o1));
    array1->remove(o1);
    //t_false(array1->contains(o1));
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

int main()
{
    //test_object1();
    test_array1();
    test_array2();
    OK("test1 passed\n");
    return 0;
}
