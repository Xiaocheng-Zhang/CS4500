#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include "helper1.h"
#include "helper2.h"
#include "helper3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc) {
    if (argv == 1) {
        printf("Usage: %s -key argument\n", argc[0]);
        exit(0);
    }
    Hashmap *command_map = new Hashmap();
    Hashmap *data_map = new Hashmap();
    //printf("%d", argv);
    read_command(command_map, argv, argc);
    int max_row = read_file(command_map, data_map);
    //hashmap_print_file(data_map);
    data_map->print_self();
    StrList *header_type = get_column_header(max_row, data_map);
    return 0;
}