#include "column.h"
#include "dataframe.h"
#include "helper.h"
#include "rower&fielder.h"
#include "schema.h"
#include "vec.h"
#include <chrono>

Schema *schema;
DataFrame *df;

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

void initialize2() {
  schema = new Schema();
  df = new DataFrame(*schema);

  IntColumn *int_col = new IntColumn();
  FloatColumn *float_col = new FloatColumn();
  BoolColumn *bool_col = new BoolColumn();
  StringColumn *string_col = new StringColumn();
  for (int i = 0; i < 100000; i++) {
    int_col->push_back(i);
    float_col->push_back(float(i));
    bool_col->push_back(true);
    string_col->push_back(new String("test String"));
  }

  df->add_column(int_col, new String("int_col"));
  df->add_column(float_col, new String("float_col"));
  df->add_column(bool_col, new String("bool_col"));
  df->add_column(string_col, new String("string_col"));
  puts("=======dataframe initialized 100,000 rows========");
}

void test2() {
  initialize();
  TestFielder *t_f = new TestFielder();
  TestFielder *t_f2 = new TestFielder();

  TestRower *r = new TestRower(t_f);
  TestRower *r2 = new TestRower(t_f2);
  puts("Time Counter start: pmap\n====================================");
  auto p_start = std::chrono::high_resolution_clock::now();
  df->pmap(*r);
  auto p_end = std::chrono::high_resolution_clock::now();
  auto p_duration =
      std::chrono::duration_cast<std::chrono::microseconds>(p_end - p_start);
  printf("Time Counter end with duration: %d microseconds\n", p_duration);
  printf("Convert to : %d seconds\n====================================\n",
         p_duration / 1000000);
  /*---------------------------------------------------------------------------------*/

  puts("Time Counter start: map\n====================================");
  auto start = std::chrono::high_resolution_clock::now();

  df->map(*r2);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  printf("Time Counter end with duration: %d microseconds\n", duration);
  printf("Convert to : %d seconds\n====================================\n",
         duration / 1000000);
  
}

void test3() {
  initialize2();
  TestFielder *t_f = new TestFielder();
  TestFielder *t_f2 = new TestFielder();
  NormalFielder *n_f = new NormalFielder();
  NormalFielder *n_f2 = new NormalFielder();

  AdvanceRower *r = new AdvanceRower(n_f, t_f);
  AdvanceRower *r2 = new AdvanceRower(n_f2, t_f2);
  puts("Time Counter start: pmap\n====================================");
  auto p_start = std::chrono::high_resolution_clock::now();
  df->pmap(*r);
  auto p_end = std::chrono::high_resolution_clock::now();
  auto p_duration =
      std::chrono::duration_cast<std::chrono::microseconds>(p_end - p_start);
  printf("Time Counter end with duration: %d microseconds\n", p_duration);
  printf("Convert to : %d seconds\n====================================\n",
         p_duration / 1000000);
  /*---------------------------------------------------------------------------------*/

  puts("Time Counter start: map\n====================================");
  auto start = std::chrono::high_resolution_clock::now();

  df->map(*r2);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  printf("Time Counter end with duration: %d microseconds\n", duration);
  printf("Convert to : %d seconds\n====================================\n",
         duration / 1000000);
  t_true(r->t_f->int_vec->equals(r2->t_f->int_vec));
}

void test1() {
  /*---------------------------------------------------------------------------------*/
  
  TestFielder *f = new TestFielder();
  TestRower *r = new TestRower(dynamic_cast<TestFielder *>(f->clone()));
  TestRower *r2 = new TestRower(f);

  puts("Time Counter start: pmap\n====================================");
  auto p_start = std::chrono::high_resolution_clock::now();

  df->pmap(*r);

  auto p_end = std::chrono::high_resolution_clock::now();
  auto p_duration =
      std::chrono::duration_cast<std::chrono::microseconds>(p_end - p_start);
  printf("Time Counter end with duration: %d microseconds\n", p_duration);
  printf("Convert to : %d seconds\n====================================\n",
         p_duration / 1000000);
  /*---------------------------------------------------------------------------------*/
  puts("Time Counter start: map\n====================================");
  auto start = std::chrono::high_resolution_clock::now();

  df->map(*r2);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  printf("Time Counter end with duration: %d microseconds\n", duration);
  printf("Convert to : %d seconds\n====================================\n",
         duration / 1000000);

  /*---------------------------------------------------------------------------------*/
  t_true(r->fielder_->float_vec->equals(r2->fielder_->float_vec));
  t_true(r->fielder_->float_vec->size() == r2->fielder_->float_vec->size());
}

/**
 * No needs for inputs because the main method reads the specific type of data
 * called datafile.txt under this work directory.
 */
int main(int argc, char* argv[]) {
  if (argc != 3) {
    puts("Usage: ./bench CS4500-as5-only-/datafile.txt");
  }
  if (strcmp(argv[2], "TestRower") == 0) {
    test2();
    return 0;
  }
  if (strcmp(argv[2], "AdvanceRower") == 0) {
    test3();
    return 0;
  }
  FILE *fd = fopen(argv[1], "r");
  char buf[1024];
  char *input = fgets(buf, 1024, fd);
  schema = new Schema();
  char cell[100];
  size_t cell_idx = 0;
  // read the headers of datafile.
  memset(cell, 0, sizeof(cell));
  for (size_t i = 0; i < strlen(input); i++) {
    if (input[i] != ',' && input[i] != '\n') {
      cell[cell_idx++] = input[i];
    } else {
      char *temp = strdup(cell);
      schema->add_column('F', new String(temp));
      cell_idx = 0;
    }
  }
  df = new DataFrame(*schema);
  Row *row = new Row(*schema);
  // read whole datafile to the end.
  while (1) {
    char *input = fgets(buf, 1024, fd);
    fflush(stdout);
    if (!input) {
      break;
    }
    size_t idx = 0;
    cell_idx = 0;
    memset(cell, 0, sizeof(cell));
    for (size_t i = 0; i < strlen(input); i++) {
      if (input[i] != ',' && input[i] != '\n') {
        cell[cell_idx++] = input[i];
      } else {
        row->set(idx++, (float)atof(cell));
      }
    }
    df->add_row(*row);
  }
  test1();
  fclose(fd);

  return 0;
}
