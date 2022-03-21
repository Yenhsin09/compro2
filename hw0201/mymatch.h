#ifndef mymatch_h
#define mymatch_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "mysplit.h"

int match(char *tmp,const char *pattern);
void ck(char ***st,int *num,int storenum,int mark[storenum]);
int mymatch(char ***pppList , const char *pStr, const char *pPattern);

#endif /* mymatch_h */
