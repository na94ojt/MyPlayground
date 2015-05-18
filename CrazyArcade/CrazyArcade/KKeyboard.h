#pragma once

#define MAX_KEY 100

class KKeyboard
{
public:
	KKeyboard(void);
	~KKeyboard(void);

	int m_KeyBuffer[MAX_KEY];		//키보드버퍼
	int OnKeyDown(int key);			//키가 내려왔을 때 (키를 눌렀을 때)
	int OnKeyUp(int key);			//키가 올라왔을 때 (키에서 손을 땟을 때)
	int FindKey(int key);			//키의 버퍼의 어떤 값들이 있는지 체크
};