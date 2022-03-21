#ifndef mysplit_h
#define mysplit_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

int find(const char *pStr, const char * pSeparator);
char *cut(const char *pStr, const char * pSeparator,char *store);
int mystrsplit(char ***ppList, int *pCounter, const char *pStr, const char * pSeparator);

#endif /* mysplit_h */
