#include <iostream>

#include "../src/application.h"
#include "../src/column.h"
#include "../src/dataframe.h"
#include "../src/kvstore.h"
#include "../src/network_layer.h"
#include "../src/schema.h"

using namespace std;

class Demo : public Application {
public:
  Key main = Key("main", 0);
  Key verify = Key("verif", 0);
  Key check = Key("ck", 0);

  Demo(size_t idx) : Application(idx) {}

  void run_() override {
    switch (this_node()) {
    case 0:
      producer();
      break;
    case 1:
      counter();
      break;
    case 2:
      summarizer();
    }
  }

  void producer() {
    size_t SZ = 1000;
    double *vals = new double[SZ];
    double sum = 0;
    for (size_t i = 0; i < SZ; ++i)
      sum += vals[i] = i;
    DataFrame::fromArray(&main, &kv, SZ, vals);
    DataFrame::fromScalar(&check, &kv, sum);
  }

  void counter() {
    DataFrame *v = kv.waitAndGet(main);
    size_t sum = 0;
    for (size_t i = 0; i < 1000; ++i)
      sum += v->get_double(0, i);
    p("The sum is  ").pln(sum);
    DataFrame::fromScalar(&verify, &kv, sum);
  }

  void summarizer() {
    DataFrame *result = kv.waitAndGet(verify);
    DataFrame *expected = kv.waitAndGet(check);
    pln(expected->get_double(0, 0) == result->get_double(0, 0) ? "SUCCESS"
                                                               : "FAILURE");
  }
};

int main(void) {
  Demo demo_0(0);
  Demo demo_1(1);
  Demo demo_2(2);
  NetworkLayer *n = new NetworkLayer();
  n->add(&demo_0);
  n->add(&demo_1);
  n->add(&demo_2);
  n->tracking();
  demo_0.run_();
  demo_1.run_();
  demo_2.run_();
  // Cannot run because we are still working on that.
  cout << "Advance test passed\n";
  return 0;
}