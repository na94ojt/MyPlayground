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
extern KERNELAPI VOID WRITE_PORT_UCHAR(IN PUCHAR Port, IN UCHAR Value);








#endif /* #ifndef _CHOBITS_H_ */