#include "chobits.h"

/*
 * GLOBAL FUNCTIONS
 */
BOOL KrnInitializeKernel(VOID);

/*
 * EXTERNEL FUNCTIONS
 */
extern BOOL HalInitializeHal(VOID);				/* hal.c */

/**********************************************************************************************************
 *                                            GLOBAL FUNTIONS                                             *
 **********************************************************************************************************/
BOOL KrnInitializeKernel(VOID)
{
	if(!HalInitializeHal()) {
		DbgPrint("HalInitializeHal() returned an error.\r\n");
		return FALSE;
	}

	return TRUE;
}
