#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Hashmap *command_map = new Hashmap();
static Hashmap *data_map = new Hashmap();

int main(int argv, char** argc) {
    if (argv == 1) {
        printf("Usage: %s -key argument\n", argc[0]);
        exit(0);
    }
    //printf("%d", argv);
    read_command(command_map, argv, argc);
    //puts("P");
    //std::cout << command_map->size();
    hashmap_print(command_map);
}