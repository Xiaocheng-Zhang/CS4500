/**
 * Demo serializing an unsigned long integer to stdout.
 *
 * Examples:
 *
 * $ make
 * $ ./serial 123
 * $ ./serial -hex 12AB34CD
 * $ ./serial 123 | ./deserial
 *
 * @author fv <f.vesely@northeastern.edu>
 */

// POSIX/BSD syscalls for file access
#include <unistd.h>

#include <assert.h>

#include "misc.h" // defines: LOG, process_args, and print_as_bytes

int main(int argc, char **argv) {
  unsigned long num = process_args(argc, argv);

  LOG("Serializing %lu as ", num);
  print_as_bytes(num);  

  LOG("Writing to stdout...\n");

  // write an integer to stdout using the write system call - analoguous to 
  // writing to a socket using send
  assert(write(STDOUT_FILENO, &num, sizeof(num)) == sizeof(num));

  LOG("Done.\n");
  return 0;
}

