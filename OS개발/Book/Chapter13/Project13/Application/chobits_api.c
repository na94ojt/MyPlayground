#include "chobits_api.h"
#include "../../string.c"

static int internel_syscall(SYSCALL_MSG *pSyscall);

/**********************************************************************************************************
 *                                            SYSTEM API CALLS                                            *
 **********************************************************************************************************/
VOID API_ExitProgram(VOID)
{
	SYSCALL_MSG syscall;

	syscall.syscall_type = SYSCALL_TERMINATED;
	internel_syscall(&syscall);

	while(1) ;
}

/**********************************************************************************************************
 *                                             SCREEN API CALLS                                           *
 **********************************************************************************************************/
VOID API_PrintText(BYTE *pText)
{
	SYSCALL_MSG syscall;

	if(pText == NULL) return;

	syscall.syscall_type = SYSCALL_PRINT_TEXT;
	syscall.parameters.PRINT_TEXT.pt_text = pText;
	internel_syscall(&syscall);
}

/**********************************************************************************************************
 *                                           INTERNAL FUNTIONS                                            *
 **********************************************************************************************************/
static int internel_syscall(SYSCALL_MSG *pSyscall)
{
#define SYSCALL_GATE			0x0048
	WORD syscall_ptr[3];

	memset(syscall_ptr, 0, sizeof(WORD)*3);
	syscall_ptr[2] = SYSCALL_GATE;

	_asm {
		push		pSyscall
		call		fword ptr syscall_ptr
		add			esp, 4
	}
}