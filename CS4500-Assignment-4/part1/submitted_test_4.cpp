#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"

void testSchema() {
  // test empty constructor
  Schema *schema1 = new Schema();
  t_true(schema1->type_vec->size_ == 0 && schema1->col_name_vec->size_ == 0 &&
         schema1->row_name_vec->size_ == 0);

  // test type_check method
  t_true(schema1->type_check('I'));
  t_false(schema1->type_check('Q'));

  // test char pointer constructor
  Schema *schema2 = new Schema("IBSF");
  t_true(schema2->type_vec->get_char(0) == 'I' &&
         schema2->type_vec->get_char(1) == 'B' &&
         schema2->type_vec->get_char(2) == 'S' &&
         schema2->type_vec->get_char(3) == 'F');

  // test adding a column with nullptr name
  schema2->add_column('I', nullptr);
  t_true(schema2->type_vec->get_char(4) == 'I');
  t_true(schema2->col_name_vec->get_String(4) == nullptr);
  // test adding a column with a non nullptr name
  schema2->add_column('B', new String("Tian"));
  t_true(schema2->type_vec->get_char(5) == 'B');
  t_true(schema2->col_name_vec->get_String(5)->equals(new String("Tian")));
  // test adding a row with nullptr name
  schema2->add_row(nullptr);
  t_true(schema2->row_name_vec->get_String(0) == nullptr);
  // test adding a row with a non nullptr name
  schema2->add_row(new String("Xia"));
  t_true(schema2->row_name_vec->get_String(1)->equals(new String("Xia")));
  // test row_name method
  t_true(schema2->row_name(1)->equals(new String("Xia")));
  // test col_name method
  t_true(schema2->col_name(5)->equals(new String("Tian")));
  // test col_type method
  t_true(schema2->col_type(5) == 'B');
  // test col_idx method
  t_true(schema2->col_idx("Tian") == 5);
  t_true(schema2->col_idx("Xiaocheng") == -1);
  // test row_idx method
  t_true(schema2->row_idx("Xia") == 1);
  t_true(schema2->col_idx("Zhang") == -1);
  // test width and length method
  t_true(schema2->width() == 6);
  t_true(schema2->length() == 2);

  // test copying constructor
  Schema *schema3 = new Schema(*schema2);
  // test if it can be mutated
  schema2->add_column('F', new String("mutation"));
  t_false(schema3->width() == schema2->width());
  OK("testSchema");
}

int main(void) {
  testSchema();
  return 0;
}