#ifndef _STRING_H_
#define _STRING_H_

/*
 * INCLUDE FILES
 */
#include "ctype.h"

/*
 * Library functions
 */
void* memset(void *pSource, int ch, size_t size);

int strcmp(const char *cs, const char *ct);
size_t strlen(const char * s);

char *strupr(char *str);

#endif /* #ifndef _STRING_H_ */