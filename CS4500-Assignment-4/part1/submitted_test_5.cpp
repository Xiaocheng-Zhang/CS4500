#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "dataframe.h"

void testBuffer() {
  // construct int buffer
  Buffer *ib = new Buffer(1);
  t_true(ib->type_ == INTEGER);
  t_true(ib->int_ == 1);
  t_true(ib->f_ == 0 && ib->b_ == false && ib->s_ == nullptr);
  Buffer *ib2 = new Buffer(2);
  Buffer *ib3 = new Buffer(1);
  // construct bool buffer
  Buffer *bb = new Buffer(false);
  t_true(bb->get_bool() == false);

  // construct String buffer
  Buffer *sb = new Buffer(new String("c"));
  t_true(sb->get_String()->equals(new String("c")));

  // test equality
  t_false(bb->equals(ib));
  t_false(ib->equals(ib2));
  t_true(ib->equals(ib3));
  OK("testBuffer");
}

int main(void) {
  testBuffer();
  return 0;
}
