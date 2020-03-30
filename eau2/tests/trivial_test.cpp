#include <iostream>

#include "../src/application.h"
#include "../src/column.h"
#include "../src/dataframe.h"
#include "../src/kvstore.h"
#include "../src/schema.h"

using namespace std;

class Trivial : public Application {
public:
  Trivial(size_t idx) : Application(idx) {}

  void run_() {
    size_t SZ = 1000 * 100;
    double *vals = new double[SZ];
    double sum = 0;
    for (size_t i = 0; i < SZ; ++i)
      sum += vals[i] = i;
    Key key("triv", 0);
    DataFrame *df = DataFrame::fromArray(&key, &kv, SZ, vals);
    assert(df->get_double(0, 1) == 1);
    DataFrame *df2 = kv.get(key);
    for (size_t i = 0; i < SZ; ++i)
      sum -= df2->get_double(0, i);
    assert(sum == 0);
    delete df;
    delete df2;
    delete[] vals;
  }
};

int main(void) {
  Trivial test(0);
  test.run_();
  cout << "Trivial test passed\n";
  return 0;
}