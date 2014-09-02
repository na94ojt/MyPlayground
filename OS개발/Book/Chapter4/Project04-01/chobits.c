/*
 *                       CHOBITS OPERATING SYSTEM
 *
 * Writer	: Yeori (Sun Kyung-Ryul)
 * E-mail	: alphamcu@hanmail.net
 * Web(kor)	: http://www.zap.pe.kr
 * Web(eng) : http://zap.pe.kr/eng
 *
 * Development Tools : # MS Visual C++ 7.0 with some tools of 6.0(previous version)
 *                     # NASM Assembler (GPL)
 *                     # MASM Assembler (MS)
 *
 * Comments : All source files are opend to public completely without any loyalty or license.
 *            I just want to share informations and techincs. ^^
 *
 */

#include "chobits.h"

/*
 * INTERNEL FUNCTIONS
 */
static void halt(char *pMsg);

int chobits_init(void)
{
	/* this code must not be excuted! it will crash the whole system. */
	halt("Chobits OS booting ERROR!!\r\n");
	return 0;
}

static void halt(char *pMsg)
{
	if(pMsg != NULL) {
		DbgPrint(pMsg);
		DbgPrint("Halting system...\r\n");
	}
	while(1) ;
}
