/**
 * Demo program deserializing an unsigned long integer from stdout.
 *
 * @author fv <f.vesely@northeastern.edu>
 */

// POSIX/BSD syscalls for file access
#include <unistd.h>

// C std library for terminal I/O and other stuff
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "misc.h" // defines: LOG and print_as_bytes


int main(int argc, char **argv) {
  unsigned long num;
  
  LOG("Reading from stdin...\n");

  // read an integer from stdin using the read system call - this is 
  // analoguous to reading from a socket
  assert(read(STDIN_FILENO, &num, sizeof(num)) == sizeof(num));
  
  LOG("Read %lu bytes: ", sizeof(num));
  print_as_bytes(num);

  LOG("Deserialized: %lu\n", num);

  LOG("Done.\n");
  return 0;
}

