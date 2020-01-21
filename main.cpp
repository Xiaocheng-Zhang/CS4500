<<<<<<< HEAD
#include "object.h"
#include "string.h"
#include "list.h"
#include "hashmap.h"
#include "integer.h"
#include "helper.h"
#include <stdio.h>

=======
#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
>>>>>>> 066e5b6a9180301b784a71df7522887394ce6ece

static Hashmap *command_map = new Hashmap();
static Hashmap *data_map = new Hashmap();

<<<<<<< HEAD
int main() {
	command_map->put(new String("-f"), new String("data.sor"));
    command_map->put(new String("-from"), new Integer(0));
    command_map->put(new String("-len"), new Integer(100));

    //mutate data_map
    read_file(command_map, data_map);
    return 0;
}
=======
int main(int argv, char** argc) {
    if (argv == 1) {
        printf("Usage: %s -key argument\n", argc[0]);
        exit(0);
    }
    //printf("%d", argv);
    read_command(command_map, argv, argc);
    //puts("P");
    hashmap_print(command_map);
}
>>>>>>> 066e5b6a9180301b784a71df7522887394ce6ece
