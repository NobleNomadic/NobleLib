/*
 * NobleLib - Minimal C standard library
 *
 * Copyright (C) 2025 NobleNomadic
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
*/
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
