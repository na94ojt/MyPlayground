#include "stdafx.h"
#include "KBomb.h"
#include "KDC.h"


KBomb::KBomb(void)
{
	m_W = 70;
	m_H = 70;
	m_Life = 0;
	m_ColorKey = RGB(255,0,255);
}


KBomb::~KBomb(void)
{
}



void KBomb::IniAction(int w,int h, int type)
{
	m_W=w;
	m_H=h;
	m_Type=type;	
	m_MaxCount=0;
	m_Loop=0;
}

int KBomb::AddAction(int aindex,int sindex,int size)
{
	if(MAX_ACTION <= aindex) return -1;

	m_ActionSIndex[aindex]=sindex;
	m_ActionSize[aindex]=size;

	return 0;
}

void KBomb::RunAction(int aindex,int loop)
{
	m_ActionIndex=aindex;
	m_Index=0;
	m_Loop=loop;
	m_MaxCount=m_ActionSize[aindex];
}

void KBomb::NextFrame()
{

	if(-1==m_Loop)
	{
		m_Index++;
		if(m_MaxCount <= m_Index )
		{		
			m_Index=0;		
		}
	}
	else if( 0 < m_Loop )
	{
		m_Index++;
		if(m_MaxCount <= m_Index )
		{
			m_Loop--;
			m_Index=0;		
		}
	}
}

void KBomb::Draw(HDC hdc)
{
	int sx,sy;

	sx=sy=0;
	if(0==m_Type) //가로형 
	{
		sx = m_Index*m_W+ m_ActionSIndex[m_ActionIndex]*m_W;		
	}
	else
	{
		//세로형 
		sy = m_Index*m_H + m_ActionSIndex[m_ActionIndex]*m_H;
	}
	
	KDC::DrawBitMapTrans(hdc,m_X,m_Y,m_W,m_H,m_hBitmap,sx,sy,m_W,m_H,m_ColorKey);
}

bool KBomb::NextFrameEx()
{
	if(-1==m_Loop)
	{
		m_Index++;
		if(m_MaxCount <= m_Index )
		{		
			m_Index=0;		
		}
		return true;
	}
	else if( 0 < m_Loop )
	{
		m_Index++;
		if(m_MaxCount <= m_Index )
		{
			m_Loop--;
			m_Index=0;		
		}
		return true;
	}
	return false;
}