#include "deserializer.h"
#include "keeper.h"
#include "serializer.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    puts("Usage: ./main serialize serialized.txt\nUsage: ./main deserialize "
         "serialized.txt");
  }
  Svec *vec = new Svec();
  Serializer *s = new Serializer();
  Keeper *k = new BasicKeeper();
  Deserializer *ds = new Deserializer();
  char *filename = argv[2];
  if (!strcmp(argv[1], "serialize")) {
    k->append(s->serialize(new String("test1")));
    k->append(s->serialize(new String("test2")));
    k->append(s->serialize(5));
    k->append(s->serialize(103));
    k->append(s->serialize(103.102));
    k->append(s->serialize(float(103.102)));
    k->append(s->serialize(true));
    k->write_file(filename);
  }
  if (!strcmp(argv[1], "deserialize"))
    ds->read_data(filename);

  return 0;
}