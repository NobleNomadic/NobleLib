// example.c - test library
#include "noblelib.h"

// Entry function
void _start() {
  // Print to STDOUT fd
  print(STDOUT, "Hello stdout\n");
  // Print log to STDERR fd
  print(STDERR, "Hello stderr\n");

  // Get a line of input and echo it back
  char buffer[128];
  print(STDOUT, "Enter text: ");
  fgets(STDIN, buffer, sizeof(buffer));

  print(STDOUT, buffer);

  // Exit with success code
  exit(0);
}
