#include <stdio.h>
#include <string.h>
#include <iostream>
#include "list.h"
#include "object.h"
#include "string.h"
#include "hashmap.h"
#include "integer.h"
#include "helper.h"
//want to check the test for previous assignment, delete the comments
//before "#include "test.h"" and "test_cases();" at line 51
//#include "test.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s -opened_file filename\n", argv[0]);
    }

    FILE* opened_file = fopen(argv[2], "r");
    if (!opened_file) {
        perror("open failed");
        return 1;
    }
    SortedStrList *sortedStrlist = new SortedStrList();
    StrList *outputList = new StrList();
    Hashmap *hashmap = new Hashmap();

    save_data_to_sortedStrList(sortedStrlist, opened_file);

    fclose(opened_file);

    hashmap_pusher(hashmap, sortedStrlist);

    String **keys = key_array_convert(hashmap);

    int max = max_int(hashmap, keys);

    for (int i = max; i > 0; i--) {
        SortedStrList *tempList = new SortedStrList();
        for (int j = 0; j < hashmap->size(); j++) {
            int cur = integer_cast(hashmap->get(keys[j]));
            if (cur == i) {
                tempList->sorted_add(keys[j]);
            }
        }
        outputList->add_all(outputList->size(), tempList);
    }

    print_list(outputList, hashmap);

    //test_cases();
    return 0;
}