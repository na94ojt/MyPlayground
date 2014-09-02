#ifndef _CHOBITS_H_
#define _CHOBITS_H_

/**********************************************************************************************************
 *                                                INCLUDE FILES                                           *
 **********************************************************************************************************/
/* common */
#include "types.h"
#include "debug.h"


/* libraries */
#include "string.h"
#include "vsprintf.h"

/* device drivers */
#include "6845crt.h"

/**********************************************************************************************************
 *                                                     HAL                                                *
 **********************************************************************************************************/
/* x86 system specific */
#define ENTER_CRITICAL_SECTION()	__asm	PUSHFD	__asm CLI
#define EXIT_CRITICAL_SECTION()		__asm	POPFD

/* These following functions are programmed in hal_asm.asm file. */
extern KERNELAPI UCHAR READ_PORT_UCHAR(IN PUCHAR Port);
extern KERNELAPI VOID WRITE_PORT_UCHAR(IN PUCHAR Port, IN UCHAR Value);
extern KERNELAPI VOID HalTaskSwitch(VOID);

/**********************************************************************************************************
 *                                               Process Manager                                          *
 **********************************************************************************************************/
typedef DWORD (*PKSTART_ROUTINE)(PVOID StartContext);

typedef enum _THREAD_STATUS {
	THREAD_STATUS_STOP,			/* dont schedule or excute */
	THREAD_STATUS_TERMINATED,	/* thread has been terminated */
	THREAD_STATUS_READY,
	THREAD_STATUS_WAITING,
	THREAD_STATUS_RUNNING,		/* only one thread of all can be assinged with this status */
} THREAD_STATUS;

KERNELAPI BOOL   PsCreateProcess(OUT PHANDLE ProcessHandle);

KERNELAPI BOOL   PsDeleteProcess(IN HANDLE ProcessHandle);
KERNELAPI BOOL   PsCreateThread(OUT PHANDLE ThreadHandle, IN HANDLE ProcessHandle, IN PKSTART_ROUTINE StartRoutine,
								IN PVOID StartContext, IN DWORD StackSize, IN BOOL AutoDelete);
KERNELAPI BOOL   PsCreateIntThread(OUT PHANDLE ThreadHandle, IN HANDLE ProcessHandle, IN PKSTART_ROUTINE StartRoutine,
								   IN PVOID StartContext, IN DWORD StackSize);
KERNELAPI BOOL   PsDeleteThread(IN HANDLE ThreadHandle);
KERNELAPI HANDLE PsGetCurrentThread(VOID);

KERNELAPI BOOL   PsSetThreadStatus(IN HANDLE ThreadHandle, IN THREAD_STATUS Status);

/**********************************************************************************************************
 *                                                Memory Manager                                          *
 **********************************************************************************************************/
KERNELAPI VOID *MmAllocateNonCachedMemory(IN ULONG NumberOfBytes);
KERNELAPI VOID  MmFreeNonCachedMemory(IN PVOID BaseAddress);

#endif /* #ifndef _CHOBITS_H_ */