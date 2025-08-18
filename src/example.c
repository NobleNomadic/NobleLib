// example.c - test library
#include "noblelib.h"

// Entry function
void main(int argc, char **argv) {
  // Print first prompt
  print(STDOUT, "Enter text: ");

  // Get input
  char buffer[128];
  fgets(buffer, sizeof(buffer), STDIN);

  // Check input
  if (stringCompare(buffer, "hi\n") == 0) {
    print(STDOUT, "Hello there!\n");
  }
  else {
    print(STDOUT, "Bye!\n");
  }

  long number = atoi(argv[1]);
  number++;
  char stringBuffer[32];
  itoa(number, stringBuffer);
  println(STDOUT, stringBuffer);

  // Exit function
  exit(0);
}
