#include "stdafx.h"
#include "CrazyArcade.h"

#include "main.h"

#include "KGame.h"
#include "KDBuffer.h"

KGame g_Game;													//�� ���� Ŭ����
KDBuffer the;

void OnCreate(HWND hWnd)
{
	g_Game.LoadBit();											//���ӿ� �ʿ��� ��Ʈ�� ���ҽ��� �ε�
	SetTimer(hWnd,1,40,NULL);									//Ű�������
	SetTimer(hWnd,2,1000,NULL);									//��ź Ÿ�̸�
	SetTimer(hWnd,3,50,NULL);									//�ִϸ��̼�
}
void OnPaint(HWND hWnd,HDC hdc)
{
	HDC bhdc = the.InitDBuffer(hdc,1050,910);					//����� �ʱ�ȭ

	g_Game.Draw(bhdc);											//����ۿ� �׷���

	the.Draw();													//����۸� ����Ʈ���ۿ� �ѷ���
}
void OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	
}
void OnTimer(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if (1 == wParam)											//1�� Ÿ�̸�
	{
		g_Game.Move();											//Ű���� ���� �˻��ϰ� ������
	}
	if (2 == wParam)											//2�� Ÿ�̸�
	{
		g_Game.CountBomb();										//��ź Ÿ�̸�
	}
	if (3 == wParam)
	{
		g_Game.NextFrame();
	}

	InvalidateRect(hWnd,NULL,FALSE);							//�׸�
}
void OnKeyDown(HWND hWnd,WPARAM wParam, LPARAM lParam)
{
	g_Game.mKeyboard.OnKeyDown(wParam);							//Ű���� ������ ��
	InvalidateRect(hWnd,NULL,FALSE);
}
void OnKeyUp(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	g_Game.mKeyboard.OnKeyUp(wParam);							//Ű���忡�� �� ���� ��
	InvalidateRect(hWnd,NULL,FALSE);
}