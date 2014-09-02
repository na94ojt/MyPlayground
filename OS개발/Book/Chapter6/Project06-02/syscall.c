#include "chobits.h"
#include "sys_desc.h"

/*
 * DEFINITIONS
 */
#define DEFAULT_STACK_SIZE			(64*1024) /* 64kbytes */

/*
 * INTERNEL FUNCTIONS
 */
static BOOL SyspSetupSysCallgate(void);

/*
 * GLOBAL VARIABLES
 */

static BYTE *m_pSyscallStack;

/**********************************************************************************************************
 *                                             GLOBAL FUNTIONS                                            *
 **********************************************************************************************************/
BOOL SysInitializeSyscall(VOID)
{
	/* setup stack for syscall */
	m_pSyscallStack = MmAllocateNonCachedMemory(DEFAULT_STACK_SIZE);
	if(m_pSyscallStack == NULL) return FALSE;

	return TRUE;
}

VOID *SysGetSyscallStackPtr(VOID)
{
	return (VOID *)m_pSyscallStack;
}

DWORD SysGetSyscallStackSize(VOID)
{
	return DEFAULT_STACK_SIZE;
}
