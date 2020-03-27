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
    delete df2;
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

// void test2() {
//   initialize();
//   TestFielder *t_f = new TestFielder();
//   TestFielder *t_f2 = new TestFielder();

//   TestRower *r = new TestRower(t_f);
//   TestRower *r2 = new TestRower(t_f2);
//   puts("Time Counter start: pmap\n====================================");
//   auto p_start = std::chrono::high_resolution_clock::now();
//   df->pmap(*r);
//   auto p_end = std::chrono::high_resolution_clock::now();
//   auto p_duration =
//       std::chrono::duration_cast<std::chrono::microseconds>(p_end - p_start);
//   printf("Time Counter end with duration: %d microseconds\n", p_duration);
//   printf("Convert to : %d seconds\n====================================\n",
//          p_duration / 1000000);
//   /*---------------------------------------------------------------------------------*/

//   puts("Time Counter start: map\n====================================");
//   auto start = std::chrono::high_resolution_clock::now();

//   df->map(*r2);

//   auto end = std::chrono::high_resolution_clock::now();
//   auto duration =
//       std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//   printf("Time Counter end with duration: %d microseconds\n", duration);
//   printf("Convert to : %d seconds\n====================================\n",
//          duration / 1000000);

// }

int main(void) {
  // IntColumn c;
  // c.push_back(3);
  // c.push_back(4);
  // c.push_back(1);
  // c.push_back(2);
  // c.push_back(5);
  // c.push_back(7);
  // c.print_self();
  // String a("a");
  // StringColumn s;
  // s.push_back(nullptr);
  // cout << s.size() << "\n";
  // cout << s.get_string(0) << "\n";

  // Schema sc;
  // sc.add_column('I', &a);
  // sc.add_column('F', nullptr);
  // cout << sc.clone_type()[1] << "\n";
  // cout << sc.clone_col_name()[0] << "\n";
  // cout << sc.clone_col_name()[1] << "\n";
  // puts("part1");
  // cout << sc.col_idx("a") << "\n";
  // cout << sc.col_idx("s") << "\n";
  // sc.add_row(nullptr);
  // sc.add_row(new String("x"));
  // cout << sc.row_idx("x") << "\n";

  // test2();
  // Key* k = new Key("a", 0);
  // CompactKey *tmp = new CompactKey(k->get_id(), k->get_position());
  // unordered_map<const char *, CompactKey *> key_map;
  // key_map[k->get_name()] = tmp;
  // cout<<key_map.at(k->get_name())->get_id();
  // puts("start");
  Trivial test(0);
  test.run_();
  return 0;
}