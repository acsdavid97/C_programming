#ifndef PROCESSARGS_H_INCLUDED
#define PROCESSARGS_H_INCLUDED

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // note that you need this for getopt to work

extern int processArgs(int argc, char *argv[], FILE **fpIn, FILE **fpOut);

#endif // PROCESSARGS_H_INCLUDED
