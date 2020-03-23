#pragma once
#include "dataframe.h"
#include "schema.h"
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

/** TestFielder used to help Rower to track all */
class TestFielder : public Fielder {
public:
  // Vec *int_vec;
  // Vec *float_vec;
  // Vec *bool_vec;
  // Vec *String_vec;
  long int_c;

  TestFielder() : Fielder() {
    int_c = 0;
    start_ = 0;
    // int_vec = new Ivec();
    // float_vec = new Fvec();
    // bool_vec = new Bvec();
    // String_vec = new Svec();
    end_ = false;
  }
  ~TestFielder() {
  }
  virtual void accept(bool b) {  }
  virtual void accept(float f) {  }
  virtual void accept(int i) {
    int_c += i - 10;
    // int_vec->append(i - 10);
  }
  virtual void accept(String *s) {  }
  virtual void done() {}

  virtual Object *clone() {
    TestFielder *temp = new TestFielder();
    // temp->int_vec = int_vec->copy();
    // temp->bool_vec = bool_vec->copy();
    // temp->float_vec = float_vec->copy();
    // temp->String_vec = String_vec->copy();
    return temp;
  }
};

// void vec_appand(Vec *v, Vec *pv, size_t type) {
//   for (size_t i = 0; i < pv->size(); i++) {
//     switch (type) {
//     case INTEGER:
//       v->append(pv->get_int(i));
//       break;
//     case BOOLEAN:
//       v->append(pv->get_bool(i));
//       break;
//     case FLOAT:
//       v->append(pv->get_float(i));
//       break;
//     case STRING:
//       v->append(pv->get_String(i));
//       break;
//     default:
//       break;
//     }
//   }
// }

/** Rower used to track all integers into a list.*/
class TestRower : public Rower {
public:
  TestFielder *fielder_;
  TestRower(TestFielder *fielder) : Rower() { fielder_ = fielder; }
  bool accept(Row &r) {
    for (size_t i = 0; i < r.width(); i++) {
      r.visit(i, *fielder_);
    }
    return true;
  }

  ~TestRower() { delete fielder_; }

  void join_delete(Rower *other) {
    TestRower *new_rower = dynamic_cast<TestRower *>(other);
    if (!new_rower) {
      return;
    }
    // std::thread int_thread(vec_appand, fielder_->int_vec,
    //                        new_rower->fielder_->int_vec, INTEGER);
    // std::thread bool_thread(vec_appand, fielder_->bool_vec,
    //                         new_rower->fielder_->bool_vec, BOOLEAN);
    // std::thread float_thread(vec_appand, fielder_->float_vec,
    //                          new_rower->fielder_->float_vec, FLOAT);
    // std::thread String_thread(vec_appand, fielder_->String_vec,
    //                           new_rower->fielder_->String_vec, STRING);
    // int_thread.join();
    // bool_thread.join();
    // float_thread.join();
    // String_thread.join();
  }

  Object *clone() {
    TestFielder *new_fielder = dynamic_cast<TestFielder *>(fielder_->clone());
    assert(new_fielder);
    TestRower *temp = new TestRower(new_fielder);
    return temp;
  }
};
