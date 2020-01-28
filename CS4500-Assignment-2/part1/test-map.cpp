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

int main(){
  test1();
  test2();
}
