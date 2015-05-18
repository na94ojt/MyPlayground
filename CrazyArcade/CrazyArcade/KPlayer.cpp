#include "stdafx.h"
#include "KPlayer.h"
#include "KDC.h"


KPlayer::KPlayer(void)
{
	m_X=0;
	m_Y=0;
	m_W=10;
	m_H=10;
	m_Speed = 10;
	m_FocusX = m_X + m_W/2;
	m_FocusY = m_Y + m_H/2;

	m_ColorKey=RGB(255,0,255);

	m_hBitmap=NULL;

	m_MaxCount=1;
	m_Index=0;
	m_Type=0; // 가로 

	m_ActionIndex=0;

	for(int i=0;i<MAX_ACTION;i++)
	{
		m_ActionSIndex[i]=0;
		m_ActionSize[i]=0;
	}

	m_MaxBomb = 10;
	m_MaxPower = 1;

	
}

KPlayer::~KPlayer(void)
{

}

void KPlayer::IniAction(int w,int h, int type)
{
	m_W=w;
	m_H=h;
	m_Type=type;	
	m_MaxCount=0;
	m_Loop=0;
}

int KPlayer::AddAction(int aindex,int sindex,int size)
{
	if(MAX_ACTION <= aindex) return -1;

	m_ActionSIndex[aindex]=sindex;
	m_ActionSize[aindex]=size;

	return 0;
}

void KPlayer::RunAction(int aindex,int loop)
{
	m_ActionIndex=aindex;
	//m_Index=0;
	m_Loop=loop;
	m_MaxCount=m_ActionSize[aindex];
}

void KPlayer::NextFrame()
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

void KPlayer::Draw(HDC hdc)
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

bool KPlayer::NextFrameEx()
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

int KPlayer::SetFocus(void)
{
	m_FocusX = (m_X + m_W/2) / m_W;
	m_FocusY = (m_Y + m_H/2) / m_H;
	return 0;
}

int KPlayer::MoveUp(int Map[13][15])
{
	if (m_FocusY == 0)
	{
		
		if (0 < m_Y-m_Speed )
		{
			m_Y-=m_Speed;
			SlideUpLeft(Map);
			SlideUpRight(Map);
			SetFocus();
		}
		
	}
	else
	{
		if (0 != Map[m_FocusY-1][m_FocusX])
		{
			RECT r1,r2,r3;						//r1=캐릭터 r2=블록또는 폭탄

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

			r2.top = (m_FocusY-1) * m_H;
			r2.bottom = r2.top + m_H;
			r2.left = m_FocusX * m_W;
			r2.right = r2.left + m_W;

			if (false == IntersectRect(&r3,&r2,&r1))
			{
				m_Y-=m_Speed;
				SlideUpLeft(Map);
				SlideUpRight(Map);
				SetFocus();
			}
		}
		else
		{
			m_Y-=m_Speed;
			SlideUpLeft(Map);
			SlideUpRight(Map);
			SetFocus();
		}
	}
	return 0;
}


int KPlayer::MoveDown(int Map[13][15])
{
	/*
	if (0 == Map[m_FocusY+1][m_FocusX] && ((0 <= m_Y+m_Speed && m_Y+m_Speed <= 910-m_W) && (0 <= m_X && m_X <= 1050)))
	{
		m_Y+=m_Speed;
		SlideDownLeft(Map);
		SlideDownRight(Map);
		SetFocus();
	}
	*/

	if (m_FocusY == 12)
	{
		
		if (m_Y+m_H+m_Speed < m_H*13)
		{
			m_Y+=m_Speed;
			SlideDownLeft(Map);
			SlideDownRight(Map);
			SetFocus();
		}
		
	}
	else
	{
		if (0 != Map[m_FocusY+1][m_FocusX])
		{
			RECT r1,r2,r3;						//r1=캐릭터 r2=블록또는 폭탄

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

			r2.top = (m_FocusY+1) * m_H;
			r2.bottom = r2.top + m_H;
			r2.left = m_FocusX * m_W;
			r2.right = r2.left + m_W;

			if (false == IntersectRect(&r3,&r2,&r1))
			{
				m_Y+=m_Speed;
				SlideDownLeft(Map);
				SlideDownRight(Map);
				SetFocus();
			}
		}
		else
		{
			m_Y+=m_Speed;
			SlideDownLeft(Map);
			SlideDownRight(Map);
			SetFocus();
		}
	}
	return 0;
}


int KPlayer::MoveLeft(int Map[13][15])
{
	/*
	if (0 == Map[m_FocusY][m_FocusX-1] && ((0 <= m_Y && m_Y <= 910) && (0 <= m_X-m_Speed && m_X-m_Speed <= 1050)))
	{
		m_X-=m_Speed;
		SlideLeftUp(Map);
		SlideLeftDown(Map);
		SetFocus();
	}
	*/

	if (m_FocusX == 0)
	{
		if (0 < m_X-m_Speed)
		{
			
				m_X-=m_Speed;
				SlideLeftUp(Map);
				SlideLeftDown(Map);
				SetFocus();
			
		}
	}
	else
	{
		if (0 != Map[m_FocusY][m_FocusX-1])
		{
			RECT r1,r2,r3;						//r1=캐릭터 r2=블록또는 폭탄

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

			r2.top = m_FocusY * m_H;
			r2.bottom = r2.top + m_H;
			r2.left = (m_FocusX-1) * m_W;
			r2.right = r2.left + m_W;

			if (false == IntersectRect(&r3,&r2,&r1))
			{
				m_X-=m_Speed;
				SlideLeftUp(Map);
				SlideLeftDown(Map);
				SetFocus();
			}
		}
		else
		{
			m_X-=m_Speed;
			SlideLeftUp(Map);
			SlideLeftDown(Map);
			SetFocus();
		}
	}
	return 0;
}


int KPlayer::MoveRight(int Map[13][15])
{
	/*
	if (0 == Map[m_FocusY][m_FocusX+1] && ((0 <= m_Y && m_Y <= 910) && (0 <= m_X+m_Speed && m_X+m_Speed <= 1050-m_W)))
	{
		m_X+=m_Speed;
		SlideRightUp(Map);
		SlideRightDown(Map);
		SetFocus();
	}
	*/

	if (m_FocusX == 14)
	{
		if (m_X+m_W+m_Speed < m_W*15)
		{
			
				m_X+=m_Speed;
				SlideRightUp(Map);
				SlideRightDown(Map);
				SetFocus();
			
		}
	}
	else
	{
		if (0 != Map[m_FocusY][m_FocusX+1])
		{
			RECT r1,r2,r3;						//r1=캐릭터 r2=블록또는 폭탄

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

			r2.top = m_FocusY * m_H;
			r2.bottom = r2.top + m_H;
			r2.left = (m_FocusX+1) * m_W;
			r2.right = r2.left + m_W;

			if (false == IntersectRect(&r3,&r2,&r1))
			{
				m_X+=m_Speed;
				SlideRightUp(Map);
				SlideRightDown(Map);
				SetFocus();
			}
		}
		else
		{
			m_X+=m_Speed;
			SlideRightUp(Map);
			SlideRightDown(Map);
			SetFocus();
		}
	}
	return 0;
}

int KPlayer::SlideUpLeft(int Map[13][15])
{
	if (0 != Map[m_FocusY-1][m_FocusX+1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY-1) * m_H + 1;
		r2.bottom = ((m_FocusY-1) * m_H) + m_H - 1;
		r2.left = (m_FocusX+1) * m_W + 1;
		r2.right = ((m_FocusX+1) * m_W) + m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_X--;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideUpRight(int Map[13][15])
{
	if (0 != Map[m_FocusY-1][m_FocusX-1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY-1)*m_H + 1;
		r2.bottom = ((m_FocusY-1) * m_H)+m_H - 1;
		r2.left = (m_FocusX-1)*m_W + 1;
		r2.right = ((m_FocusX-1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_X++;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideDownLeft(int Map[13][15])
{
	if (0 != Map[m_FocusY+1][m_FocusX+1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY+1)*m_H + 1;
		r2.bottom = ((m_FocusY+1) * m_H)+m_H - 1;
		r2.left = (m_FocusX+1)*m_W + 1;
		r2.right = ((m_FocusX+1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_X--;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideDownRight(int Map[13][15])
{
	if (0 != Map[m_FocusY+1][m_FocusX-1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY+1)*m_H + 1;
		r2.bottom = ((m_FocusY+1) * m_H)+m_H - 1;
		r2.left = (m_FocusX-1)*m_W + 1;
		r2.right = ((m_FocusX-1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_X++;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideLeftDown(int  Map[13][15])
{
	if (0 != Map[m_FocusY-1][m_FocusX-1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY-1)*m_H + 1;
		r2.bottom = ((m_FocusY-1) * m_H)+m_H - 1;
		r2.left = (m_FocusX-1)*m_W + 1;
		r2.right = ((m_FocusX-1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_Y++;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideLeftUp(int Map[13][15])
{
	if (0 != Map[m_FocusY+1][m_FocusX-1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY+1)*m_H + 1;
		r2.bottom = ((m_FocusY+1) * m_H)+m_H - 1;
		r2.left = (m_FocusX-1)*m_W + 1;
		r2.right = ((m_FocusX-1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_Y--;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideRightDown(int Map[13][15])
{
	if (0 != Map[m_FocusY-1][m_FocusX+1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY-1)*m_H + 1;
		r2.bottom = ((m_FocusY-1) * m_H)+m_H - 1;
		r2.left = (m_FocusX+1)*m_W + 1;
		r2.right = ((m_FocusX+1) * m_W)+m_H - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_Y++;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SlideRightUp(int Map[13][15])
{
	if (0 != Map[m_FocusY+1][m_FocusX+1])
	{
		RECT r1,r2,r3;

		r1.top = m_Y;
		r1.bottom = m_Y + m_H;
		r1.left = m_X;
		r1.right = m_X + m_W;

		r2.top = (m_FocusY+1)*m_H + 1;
		r2.bottom = ((m_FocusY+1) * m_H)+m_H - 1;
		r2.left = (m_FocusX+1)*m_W + 1;
		r2.right = ((m_FocusX+1) * m_W)+m_W - 1;

		while (true == IntersectRect(&r3,&r2,&r1))
		{
			m_Y--;
			SetFocus();

			r1.top = m_Y;
			r1.bottom = m_Y + m_H;
			r1.left = m_X;
			r1.right = m_X + m_W;

		}

		return 0;
	}
}


int KPlayer::SetBomb(int Map[13][15],HBITMAP bitmap)
{
	if (0 == Map[m_FocusY][m_FocusX])
	{
		for (int i = 0; i<m_MaxBomb; i++)
		{
			if (0 == m_Bomb[i].m_Life)
			{
				m_Bomb[i].m_Life = 5;
				m_Bomb[i].m_X = (m_FocusX * m_W) / m_W * m_W;
				m_Bomb[i].m_Y = (m_FocusY * m_H) / m_H * m_H;

				//m_Bomb[i].RunAction(0,1);

				Map[m_Bomb[i].m_Y/m_H][m_Bomb[i].m_X/m_W] = 5;
				break;
			}
		}
	}
	return 0;
}

int KPlayer::LoadhBomb(HBITMAP hBomb)
{
	for (int i = 0; i<10; i++)
	{
		m_Bomb[i].m_hBitmap = hBomb;
		m_Bomb[i].IniAction(m_Bomb[i].m_W,m_Bomb[i].m_H,0);
		m_Bomb[i].AddAction(0,0,4);
	}

	return 0;
}
