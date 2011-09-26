#ifndef JAM_IO_H
#define JAM_IO_H

#include <stdbool.h>
bool runInBackground(char**, int*);
char** readLine(int*);
void printToStdout();
void printToFile();

#endif
