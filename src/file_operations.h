#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns an array of strings that represent the file (Doesnt include newlines)
extern char ** getLinesFromFile(char * filename, unsigned long * fSize);

#endif