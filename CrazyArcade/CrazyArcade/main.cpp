#include "stdafx.h"
#include "CrazyArcade.h"

#include "main.h"

#include "KGame.h"
#include "KDBuffer.h"

KGame g_Game;													//주 게임 클래스
KDBuffer the;

void OnCreate(HWND hWnd)
{
	g_Game.LoadBit();											//게임에 필요한 비트맵 리소스들 로드
	SetTimer(hWnd,1,40,NULL);									//키보드버퍼
	SetTimer(hWnd,2,1000,NULL);									//폭탄 타이머
	SetTimer(hWnd,3,50,NULL);									//애니메이션
}
void OnPaint(HWND hWnd,HDC hdc)
{
	HDC bhdc = the.InitDBuffer(hdc,1050,910);					//백버퍼 초기화

	g_Game.Draw(bhdc);											//백버퍼에 그려줌

	the.Draw();													//백버퍼를 프론트버퍼에 뿌려줌
}
void OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	
}
void OnTimer(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if (1 == wParam)											//1번 타이머
	{
		g_Game.Move();											//키보드 버퍼 검사하고 움직임
	}
	if (2 == wParam)											//2번 타이머
	{
		g_Game.CountBomb();										//폭탄 타이머
	}
	if (3 == wParam)
	{
		g_Game.NextFrame();
	}

	InvalidateRect(hWnd,NULL,FALSE);							//그림
}
void OnKeyDown(HWND hWnd,WPARAM wParam, LPARAM lParam)
{
	g_Game.mKeyboard.OnKeyDown(wParam);							//키보드 눌렀을 때
	InvalidateRect(hWnd,NULL,FALSE);
}
void OnKeyUp(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	g_Game.mKeyboard.OnKeyUp(wParam);							//키보드에서 손 땟을 때
	InvalidateRect(hWnd,NULL,FALSE);
}