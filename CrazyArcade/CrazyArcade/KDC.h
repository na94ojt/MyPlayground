#pragma once
class KDC
{
public:
	KDC(void);
	~KDC(void);
	static int DrawBitMap(void);
	static int DrawBitMap(HDC hdc, int x, int y, int w, int h, HBITMAP bitmap, int xx, int xy, int xw, int xh);

	static int DrawBitMapTrans(HDC hdc, int x, int y, int w, int h, HBITMAP bitmap, int sx, int sy, int sw, int sh,COLORREF color);

	static HBITMAP OpenImageFromRC(HINSTANCE hInst,int rid);
	static HBITMAP OpenImageFromBMPFile(HINSTANCE hInst,char* filename);

};

