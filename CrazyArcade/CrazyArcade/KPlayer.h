#pragma once

#include <vector>
#include "KBomb.h"

#define MAX_ACTION  10

using namespace std;

class KPlayer
{
	
public:
	KPlayer(void);
	~KPlayer(void);


	int m_X;
	int m_Y;
	int m_W;
	int m_H;
	int m_Speed;
	int m_FocusX;
	int m_FocusY;
	int m_MaxBomb;
	int m_MaxPower;

	int MoveUp(int Map[13][15]);
	int MoveDown(int Map[13][15]);
	int MoveLeft(int Map[13][15]);
	int MoveRight(int Map[13][15]);

	int SlideUpLeft(int Map[13][15]);
	int SlideUpRight(int Map[13][15]);
	int SlideDownLeft(int Map[13][15]);
	int SlideDownRight(int Map[13][15]);
	int SlideLeftDown(int  Map[13][15]);
	int SlideLeftUp(int Map[13][15]);
	int SlideRightDown(int Map[13][15]);
	int SlideRightUp(int Map[13][15]);

	KBomb m_Bomb[10];

	//////////////////////////////////////////////////////////////////////
	COLORREF m_ColorKey;

	HBITMAP m_hBitmap;
	//for animation
	int m_MaxCount;
	int m_Index;
	int m_Type; // 0:가로, 1:세로 
	int m_Loop;
	int m_ActionIndex;

	
	int m_ActionSIndex[MAX_ACTION];
	int m_ActionSize[MAX_ACTION];


	void Draw(HDC hdc);
	void IniAction(int w,int h, int type );
	void RunAction(int aindex,int loop);
	void NextFrame();
	bool NextFrameEx();

	int AddAction(int aindex,int sindex,int size);

	int SetFocus(void);
	int SetBomb(int Map[13][15],HBITMAP bitmap);
	int AddBomb(void);
	int LoadhBomb(HBITMAP hBomb);
};

