#include <iostream>

#include "application.h"
#include "column.h"
#include "dataframe.h"
#include "kvstore.h"
#include "rower&fielder.h"
#include "schema.h"

using namespace std;

Schema *schema;
DataFrame *df;

class Trivial : public Application {
public:
  Trivial(size_t idx) : Application(idx) {}

  void run_() {
    size_t SZ = 1000;
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
    //delete df2;
  }
};

void initialize() {
  schema = new Schema();
  df = new DataFrame(*schema);

  IntColumn *int_col = new IntColumn();
  FloatColumn *float_col = new FloatColumn();
  BoolColumn *bool_col = new BoolColumn();
  StringColumn *string_col = new StringColumn();
  for (int i = 0; i < 50000; i++) {
    int_col->push_back(i);
    float_col->push_back(float(i));
    bool_col->push_back(true);
    string_col->push_back(new String("test String"));
  }

  df->add_column(int_col, new String("int_col"));
  df->add_column(float_col, new String("float_col"));
  df->add_column(bool_col, new String("bool_col"));
  df->add_column(string_col, new String("string_col"));
  puts("=======dataframe initialized 100,000 rows =======");
}

int main(void) {
  Trivial test(0);
  test.run_();
  cout << "Trivial test passed" << "\n";
  return 0;
}