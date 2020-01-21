#include "object.h"
#include "string.h"
#include "list.h"
#include "hashmap.h"
#include "integer.h"
#include "helper.h"
#include <stdio.h>


static Hashmap *command_map = new Hashmap();
static Hashmap *data_map = new Hashmap();

int main() {
	command_map->put(new String("-f"), new String("data.sor"));
    command_map->put(new String("-from"), new Integer(0));
    command_map->put(new String("-len"), new Integer(100));

    //mutate data_map
    read_file(command_map, data_map);
    return 0;
}
