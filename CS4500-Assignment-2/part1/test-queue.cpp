#include "queue.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>

void FAIL() { exit(1); }
void OK(const char *m) { std::cout << m << "\n"; }
void t_true(bool p) {
  if (!p)
    FAIL();
}
void t_false(bool p) {
  if (p)
    FAIL();
}

// tests strings
void test1() {
  String *s = new String("Hello");
  String *t = new String("World");
  String *s1 = new String(" Hello ");
  String *s2 = new String("He");
  String *u = s->concat(t);
  t_true(s->equals(s));
  t_false(s->equals(t));
  t_false(s->equals(u));
  t_true(s->compare(s) == 0);
  t_true(s->compare(t) != 0);
  t_false(s->equals(s1));
  s1->trim();
  t_true(s->equals(s1));
  t_true(s->contains(s2));

  OK("test1 passed");
}

// tests queues
void test2() {
  Queue *a = new Queue();
  Queue *b = new Queue();
  Object *s = new String("Hello");
  Object *t = new String("World");
  Object *s1 = new String("Hello");
  Object *s2 = new String("He");
  a->enqueue(s);
  a->enqueue(t);
  a->enqueue(s1);
  b->enqueue(s1);
  b->enqueue(s2);
  b->enqueue(s2);

  t_true((a->peek())->equals(b->peek()));
  t_true((a->dequeue())->equals(b->dequeue()));
  t_false((a->dequeue())->equals(b->dequeue()));
  t_false((a->peek())->equals(b->peek()));
  t_true((a->size()) == b->size());
  b->dequeue();
  t_false((a->size()) == b->size());
  OK("test2 passed");
}

void none_spec_test1() {
  Queue *a = new Queue();
  Queue *b = new Queue();
  Object *s = new String("ABC");
  Object *t = new String("ABC");
  a->enqueue(s);
  b->enqueue(s);
  t_true(a->equals(b));

  Object *d = new String("D");
  Object *e = new String("E");
  a->enqueue(d);
  a->enqueue(e);
  b->enqueue(d);
  b->enqueue(e);
  t_true(a->equals(b));
  OK("none_spec_test1 passed");
}

void none_spec_test2() {
  Queue *a = new Queue();
  Queue *b = new Queue();
  Object *s = new String("ABC");
  Object *t = new String("ABC");
  a->enqueue(s);
  b->enqueue(s);
  t_true(a->equals(b));

  Object *d = new String("D");
  Object *e = new String("E");
  a->enqueue(d);
  a->enqueue(e);
  b->enqueue(e);
  b->enqueue(d);
  t_false(a->equals(b));
  OK("none_spec_test2 passed");
}

int main() {
  test1();
  test2();
  none_spec_test1();
  none_spec_test2();
  /** puts method help to check tests passed (made by implementor team)*/
  //puts("All tests in test-queue.cpp passed!");
  return 0;
}
