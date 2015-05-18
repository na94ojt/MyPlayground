#include "stdafx.h"
#include "KKeyboard.h"


KKeyboard::KKeyboard(void)
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		m_KeyBuffer[i] = -1;					//-1이면 아무것도 없는거임
	}
}


KKeyboard::~KKeyboard(void)
{
}


int KKeyboard::OnKeyDown(int key)
{
	if (-1 == FindKey(key))						//키 버퍼에 누른 값이 없다면
	{
		for (int i = 0; i<MAX_KEY; i++)			//비어있는 방 찾는 반복문
		{
			if (-1 == m_KeyBuffer[i])			//비어있으면
			{
				m_KeyBuffer[i] = key;			//누른 키보드 자판의 값을 버퍼에 저장
				return 0;						//함수 종료
			}
		}
	}
	return 0;
}


int KKeyboard::OnKeyUp(int key)
{
	int index = FindKey(key);					//FindKey에서 해당 키값의 인덱스를 찾아옴

	if (-1 != index)							//비어있지 않다면
	{
		m_KeyBuffer[index] = -1;				//비움
	}

	return 0;
}


int KKeyboard::FindKey(int key)					  //해당 키가 버퍼에 있는지 확인하는 메소드
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		if (key == m_KeyBuffer[i])
		{
			return i;
		}
	}

	return -1;
}