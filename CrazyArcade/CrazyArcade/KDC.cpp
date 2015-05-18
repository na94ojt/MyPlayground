#include "stdafx.h"
#include "KDC.h"

#pragma comment(lib,"MSimg32.lib")


KDC::KDC(void)
{
}


KDC::~KDC(void)
{
}


int KDC::DrawBitMap(void)
{
	return 0;
}


int KDC::DrawBitMap(HDC hdc, int x, int y, int w, int h, HBITMAP bitmap, int sx, int sy, int sw, int sh)
{
	HDC memDC = CreateCompatibleDC(hdc);							//�ڵ� ����

	HBITMAP pOld = (HBITMAP)SelectObject(memDC,bitmap);				//���� ���� ���� �����ϰ� memDC�ڵ鿡 bitmapObject ����

	StretchBlt(hdc,x,y,w,h,memDC,sx,sy,sw,sh,SRCCOPY);				//�׸��׸�

	SelectObject(memDC,pOld);										//������ Object�� �ٽ� ����
	DeleteDC(memDC);												//memDC ����
	return 0;
}
int KDC::DrawBitMapTrans(HDC hdc, int x, int y, int w, int h, HBITMAP bitmap, int sx, int sy, int sw, int sh,COLORREF color)
{   
	HDC memDC = CreateCompatibleDC(hdc);

	HBITMAP pOld = (HBITMAP)SelectObject(memDC,bitmap);

	TransparentBlt(hdc,x,y,w,h,memDC,sx,sy,sw,sh,color);

	SelectObject(memDC,pOld);
	DeleteDC(memDC);
	
	return 0;
}

HBITMAP KDC::OpenImageFromRC(HINSTANCE hInst,int rid)
{
	HBITMAP hBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(rid));

	return hBitmap;
}

HBITMAP KDC::OpenImageFromBMPFile(HINSTANCE hInst,char* filename)
{

	HBITMAP hBitmap=(HBITMAP)LoadImage(hInst, filename, IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE); 

	return hBitmap;
}