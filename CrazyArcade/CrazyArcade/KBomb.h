#pragma once

#define MAX_ACTION 10

class KBomb
{
public:
	KBomb(void);
	~KBomb(void);

	int m_X;
	int m_Y;
	int m_W;
	int m_H;
	int m_Life;
	
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
	
};

