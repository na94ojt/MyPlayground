#pragma once

#define MAX_KEY 100

class KKeyboard
{
public:
	KKeyboard(void);
	~KKeyboard(void);

	int m_KeyBuffer[MAX_KEY];		//Ű�������
	int OnKeyDown(int key);			//Ű�� �������� �� (Ű�� ������ ��)
	int OnKeyUp(int key);			//Ű�� �ö���� �� (Ű���� ���� ���� ��)
	int FindKey(int key);			//Ű�� ������ � ������ �ִ��� üũ
};