#include "stdafx.h"
#include "KKeyboard.h"


KKeyboard::KKeyboard(void)
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		m_KeyBuffer[i] = -1;					//-1�̸� �ƹ��͵� ���°���
	}
}


KKeyboard::~KKeyboard(void)
{
}


int KKeyboard::OnKeyDown(int key)
{
	if (-1 == FindKey(key))						//Ű ���ۿ� ���� ���� ���ٸ�
	{
		for (int i = 0; i<MAX_KEY; i++)			//����ִ� �� ã�� �ݺ���
		{
			if (-1 == m_KeyBuffer[i])			//���������
			{
				m_KeyBuffer[i] = key;			//���� Ű���� ������ ���� ���ۿ� ����
				return 0;						//�Լ� ����
			}
		}
	}
	return 0;
}


int KKeyboard::OnKeyUp(int key)
{
	int index = FindKey(key);					//FindKey���� �ش� Ű���� �ε����� ã�ƿ�

	if (-1 != index)							//������� �ʴٸ�
	{
		m_KeyBuffer[index] = -1;				//���
	}

	return 0;
}


int KKeyboard::FindKey(int key)					  //�ش� Ű�� ���ۿ� �ִ��� Ȯ���ϴ� �޼ҵ�
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