#include "chobits.h"

/*
 * GLOBAL FUNCTIONS
 */
BOOL KrnInitializeKernel(VOID);

/*
 * EXTERNEL FUNCTIONS
 */
extern BOOL HalInitializeHal(VOID);				/* hal.c */
extern BOOL MmkInitializeMemoryManager(VOID);	/* mmanager.c */
extern BOOL PskInitializeProcessManager(VOID);	/* process.c */
extern BOOL SysInitializeSyscall(VOID); /* syscall.c */

/**********************************************************************************************************
 *                                            GLOBAL FUNTIONS                                             *
 **********************************************************************************************************/
BOOL KrnInitializeKernel(VOID)
{
	if(!HalInitializeHal()) {
		DbgPrint("HalInitializeHal() returned an error.\r\n");
		return FALSE;
	}

	if(!MmkInitializeMemoryManager()) {		/* first of all */
		DbgPrint("MmkInitializeMemoryManager() returned an error.\r\n");
		return FALSE;
	}

	if(!PskInitializeProcessManager()) {
		DbgPrint("PskInitializeProcessManager() returned an error.\r\n");
		return FALSE;
	}

	if(!SysInitializeSyscall()) {
		DbgPrint("SysInitializeSyscall() returned an error.\r\n");
		return FALSE;
	}

	return TRUE;
}
