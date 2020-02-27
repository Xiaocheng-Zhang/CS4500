#pragma once
#include "schema.h"
#include "vec.h"
#include "dataframe.h"
#include <iostream>
#include <unistd.h>

/** TestFielder used to help Rower to track all */
class TestFielder : public Fielder {
public:
  Vec *int_vec;
  Vec *float_vec;
  Vec *bool_vec;
  Vec *String_vec;
  long int_c;

  TestFielder() : Fielder() {
    int_c = 0;
    start_ = 0;
    int_vec = new Ivec();
    float_vec = new Fvec();
    bool_vec = new Bvec();
    String_vec = new Svec();
    end_ = false;
  }
  ~TestFielder() {
    delete int_vec;
    delete float_vec;
    delete bool_vec;
    delete String_vec;
  }
  virtual void accept(bool b) { bool_vec->append(!b); }
  virtual void accept(float f) { float_vec->append(100 * f); }
  virtual void accept(int i) {
    int_c += i - 10;
    int_vec->append(i - 10);
  }
  virtual void accept(String *s) { String_vec->append(s); }
  virtual void done() {}

  virtual Object *clone() {
    TestFielder *temp = new TestFielder();
    temp->int_vec = int_vec->copy();
    temp->bool_vec = bool_vec->copy();
    temp->float_vec = float_vec->copy();
    temp->String_vec = String_vec->copy();
    return temp;
  }
};

void vec_appand(Vec *v, Vec *pv, size_t type) {
  for (size_t i = 0; i < pv->size(); i++) {
    switch (type) {
    case INTEGER:
      v->append(pv->get_int(i));
      break;
    case BOOLEAN:
      v->append(pv->get_bool(i));
      break;
    case FLOAT:
      v->append(pv->get_float(i));
      break;
    case STRING:
      v->append(pv->get_String(i));
      break;
    default:
      break;
    }
  }
}

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
    std::thread int_thread(vec_appand, fielder_->int_vec,
                           new_rower->fielder_->int_vec, INTEGER);
    std::thread bool_thread(vec_appand, fielder_->bool_vec,
                            new_rower->fielder_->bool_vec, BOOLEAN);
    std::thread float_thread(vec_appand, fielder_->float_vec,
                             new_rower->fielder_->float_vec, FLOAT);
    std::thread String_thread(vec_appand, fielder_->String_vec,
                              new_rower->fielder_->String_vec, STRING);
    int_thread.join();
    bool_thread.join();
    float_thread.join();
    String_thread.join();
  }

  Object *clone() {
    TestFielder *new_fielder = dynamic_cast<TestFielder *>(fielder_->clone());
    assert(new_fielder);
    TestRower *temp = new TestRower(new_fielder);
    return temp;
  }
};

class NormalFielder : public Fielder {
public:
  long acc_int;
  long acc_true;
  long acc_false;
  long acc_float;
  Svec *string_vec;
  NormalFielder() : Fielder() {
    start_ = false;
    string_vec = new Svec();
    acc_int = 0;
    acc_true = 0;
    acc_false = 0;
  }
  ~NormalFielder() { delete string_vec; }

  virtual void start(size_t r) { start_ = r; }

  /** Called for fields of the argument's type with the value of the field.
   */
  virtual void accept(bool b) {
    if (b) {
      acc_true++;
    } else {
      acc_false++;
    }
  }
  virtual void accept(float f) { acc_float++; }
  virtual void accept(int i) { acc_int += i; }
  virtual void accept(String *s) { string_vec->append(s); }

  /** Called when all fields have been seen. */
  virtual void done() { end_ = true; }

  virtual Object *clone() {
    NormalFielder *f = new NormalFielder();
    f->acc_false = acc_false;
    f->acc_float = acc_float;
    f->acc_int = acc_int;
    f->acc_true = acc_true;
    f->string_vec = dynamic_cast<Svec*>(string_vec->copy());
    return f;
  }
};

class AdvanceRower : public Rower {
public:
  NormalFielder *n_f;
  TestFielder *t_f;
  DataFrame *df;
  size_t idx;
  AdvanceRower(NormalFielder *nf, TestFielder *tf) : Rower() {
    n_f = nf;
    t_f = tf;
    idx = 0;
    df = new DataFrame(*(new Schema()));
  }
  virtual bool accept(Row &r) { 
    for (size_t i = 0; i < r.size_; i++) {
      r.visit(i, *n_f);
      for (size_t k = 0; k < r.size_; k++) {
        r.visit(k, *t_f);
      }
    }
    if (n_f->acc_true >= n_f->acc_false) {
      StringColumn *c = new StringColumn();
      c->val_ = t_f->String_vec;
      char buf[10];
      sprintf(buf, "%09d", idx);
      buf[9] = 0;
      idx++;
      df->add_column(c, new String(buf));
      return true;
    }
    return false;
  }

  virtual void join_delete(Rower *other) {
    AdvanceRower *new_rower = dynamic_cast<AdvanceRower *>(other);
    if (!new_rower) {
      return;
    }
    for (size_t j = 0; j < new_rower->df->schema_->width(); j++) {
      char buf[10];
      sprintf(buf, "%09d", idx);
      buf[9] = 0;
      idx++;
      df->add_column(new_rower->df->table_->get_Column(j), new String(buf));
    }
  }
  Object *clone() {
    NormalFielder *new_fielder = dynamic_cast<NormalFielder *>(n_f->clone());
    TestFielder *new_fielder2 = dynamic_cast<TestFielder *>(t_f->clone());
    assert(new_fielder && new_fielder2);
    AdvanceRower *temp = new AdvanceRower(new_fielder, new_fielder2);
    return temp;
  }
};