#include "string.h"

#ifndef NULL
# define NULL ((void *)0)
#endif

void* memset(void *pSource, int ch, size_t size)
{
	size_t i;

	for(i=0; i<size; i++)
		*(((char *)pSource)+i) = (char)ch;

	return pSource;
}

char *strupr(char *str)
{
	char *cp = str;

	while(*cp != '\0') {
		if(*cp >= 'a' && *cp <= 'z')
			*cp = *cp-'a' + 'A';
		cp++;
	}

	return str;
}

/* codes from Linux */
int strcmp(const char *cs, const char *ct)
{
	char __res;

	while(1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}

/* codes from Linux */
size_t strlen(const char * s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}
