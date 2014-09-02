#ifndef _DIRECT_Y_H_
#define _DIRECT_Y_H_

/**********************************************************************************************************
 *                                                INCLUDE FILES                                           *
 **********************************************************************************************************/
#include "chobits.h"


/**********************************************************************************************************
 *                                               EXPORTED FUNCTIONS                                       *
 **********************************************************************************************************/
KERNELAPI BOOL			DySetVideoMode(DY_VIDEO_MODE mode, HANDLE hPalette);
KERNELAPI DY_VIDEO_MODE	DyGetCurrentVideoMode(VOID);

KERNELAPI HANDLE		DyLoadBitmap(char *pFilename);
KERNELAPI HANDLE		DyGetPaletteHandle(HANDLE hBitmap);
KERNELAPI BOOL			DyGetBitmapInfo(HANDLE hBitmap, BITMAP_INFO *pBitmapInfo);
KERNELAPI BOOL			DyBitBlt(HANDLE hBitmap, WORD scrX, WORD scrY, DWORD startImgX, DWORD startImgY,
								 DWORD cxToBeDisplayed, DWORD cyToBeDisplayed, RGB_COLOR *pMaskColor); /* pMaskColor = optional */
KERNELAPI VOID			DyCloseBitmapHandle(HANDLE hBitmap);


#endif // #ifndef _DIRECT_Y_H_