#ifndef _6845_CRT_DRIVER_HEADER_FILE_
#define _6845_CRT_DRIVER_HEADER_FILE_

/**********************************************************************************************************
 *                                                INCLUDE FILES                                           *
 **********************************************************************************************************/
#include "chobits.h"

/**********************************************************************************************************
 *                                               DRIVER FUNCTIONS                                         *
 **********************************************************************************************************/

KERNELAPI VOID CrtGetCursorPos(BYTE *pX, BYTE *pY);


KERNELAPI BOOL CrtPrintText(LPCSTR pText);

KERNELAPI BOOL CrtPrintTextXYWithAttr(LPCSTR pText, WORD x, WORD y, UCHAR Attr);

KERNELAPI int  CrtPrintf(const char *fmt, ...); /* by using standard c library */



#endif /* #ifndef _6845_CRT_DRIVER_HEADER_FILE_ */