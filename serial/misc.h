/**
 * Helper functions and macros for serial and deserial.
 *
 * @author fv <f.vesely@northeastern.edu>
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LOG(...) fprintf(stderr, "(" __FILE__ ") " __VA_ARGS__);

/**
 * Processes arguments and returns the number to be serialized.
 *
 * @param argc
 * @param argv
 *
 * @return Number to serialize.
 */
unsigned long process_args(int argc, char **argv) {
  assert(argc > 1);
  // We expect the number argument as first by default
  char *numarg = argv[1];
  int base = 10; // default base

  if (!strcmp(argv[1], "-hex")) { // if first argument is "-hex"
    assert(argc > 2);   // make sure there's at least one more arg
    base = 16;          // switch base to hex
    numarg = argv[2];   // take the second argument as the number
  }

  char *end; // will hold the pointer to the end of the string
  unsigned long num = strtol(numarg, &end, base);

  // check if we parsed the whole argument
  if (numarg == end || *end != '\0') {
    LOG("Couldn't parse argument as number: %s\n", numarg);
    exit(1);
  }

  return num;
}

/**
 * Pretty-print the given unsigned integer as a sequence of bytes in machine 
 * order.
 */
void print_as_bytes(unsigned long num) {
  unsigned char *buf = reinterpret_cast<unsigned char*>(&num);
  for (int i = 0; i < sizeof(num); i++) {
    fprintf(stderr, "0x%02X ", buf[i]); 
  }
  fputc('\n', stderr);
}


