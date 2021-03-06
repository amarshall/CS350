#ifndef JAM_IO_H
#define JAM_IO_H

#include <stdbool.h>

bool runInBackground(char**, int*);
char* fileRedirect(char**, int*, const char*);
char* findInputFile(char**, int*);
char* findOutputFile(char**, int*);
char** readLine(int*);
void printToStdout();
void printToFile();

#endif
