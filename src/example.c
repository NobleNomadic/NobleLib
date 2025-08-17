// example.c - test library
#include "noblelib.h"

// Entry function
void _start() {
  print(STDOUT, "Hello stdout!\n");
  print(STDERR, "Hello stderr!\n");

  // Print to a new file
  int newfd = open("hello.txt", 0100 | 1 | 01000, 0644);
  print(newfd, "Hi file!\n");
  exit(0);
}
