#include "string.h"
#include "queue.h"
#include <stdlib.h>
#include <iostream>

void FAIL() {   exit(1);    }
void OK(const char* m) { std::cout << m << "\n"; }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }

//tests strings
void test1() {
  String * s = new String("Hello");
  String * t = new String("World");
  String * s1 = new String(" Hello ");
  String * s2 = new String("He");
  String * u = s->concat(t);
  t_true(s->equals(s));
  t_false(s->equals(t));
  t_false(s->equals(u));
  t_true(s->compare(s) == 0);
  t_false(s->compare(t) != 0);
  t_false(s->equals(s1));
  t_true(s->equals(s1->trim()));
  t_true(s->contains(s2));
  
  OK("1");
}

//tests queues
void test2() {
  Queue * a = new Queue();
  Queue * b = new Queue();
  Object * s = new String("Hello");
  Object * t = new String("World");
  Object * s1 = new String(" Hello ");
  Object * s2 = new String("He");
  a->enqueue(s);
  a->enqueue(t);
  b->enqueue(s1);
  b->enqueue(s2);
  
  t_true((a->peek())->equals(b->peek()));
  t_true((a->dequeue())->equals(b->dequeue()));
  t_false((a->dequeue())->equals(b->dequeue()));
  t_false((a->peek())->equals(b->peek()));
  t_true((a->size()) == b->size());
  b->dequeue();
  t_false((a->size()) == b->size());
}

int main() {
  test1();
  test2();
  return 0;
}
