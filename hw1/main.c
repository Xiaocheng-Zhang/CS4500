#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int string_equals(char* s, char* c) {
    return strcmp(s, c) == 0;
}

int string_partial_equals(const char* s, const char* c, int n) {
    return strncmp(s, c, n) == 0;
}

void print(size_t ms, char* s, char* c) {
    printf("%d %s %s\n", ms, s, c);
}

void executor(int argc, char** argv) {
    size_t ms = 0;
    char* s = 0;
    char* c;
    c = malloc(1000);
    int types = 0;
    for (int i = 1; i < argc; i++) {
        if (string_equals("-i", argv[i]) && types < 3) {
            i++;
            types++;
            if (i < argc && atoi(argv[i]) >= 0) {
                ms = atoi(argv[i]);
            }
            if (i < argc && atoi(argv[i]) < 0) {
                printf("Exception: -i must follow a positive integer.\n");
            }
        }
        else if (string_equals("-f", argv[i]) && types < 3) {
            i++;
            if (i < argc) {
                s = strdup(argv[i]);
                types++;
            }
        }
        else if (types < 3) {
            int count = 0;
            for (int k = i; k < argc; k++) {
                if (string_equals("-i", argv[k]) || string_equals("-f", argv[k])) {
                    printf("Optional comment comming at the end of the argument list.\n");
                    return;
                }
                strcat(c, argv[k]);
                strcat(c, " ");
                count = k - i;
            }
            i+= count;
            types++;
        }
    }
    print(ms, s, c);
    if (s) {
        free(s);
    }
    if (s) {
        free(c);
    }
}

int main(int argc, char* argv[]) {
    if (argc  == 1) {
        printf("Usage: %s \"message\"-i integer -f message\n",
        argv[0]);
        exit(0);
    }
    
    executor(argc, argv);
    return 0;
}
