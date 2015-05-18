#include "stdafx.h"
#include "resource.h"
#include "KGame.h"

#include <fstream>

using namespace std;

KGame::KGame(void)
{
	LoadMap("Map1.txt");																			//맵 로드
	
}


KGame::~KGame(void)
{
}


int KGame::Draw(HDC hdc)
{
	KDC::DrawBitMap(hdc,0,0,MY_W*15,MY_H*13,m_hBackBit,0,0,MY_W*15,MY_H*13);						//배경맵 그림

	for (int i = 0; i<Player_1.m_MaxBomb; i++)
	{
		//폭탄 그림
		if (0 < Player_1.m_Bomb[i].m_Life)
		{
			Player_1.m_Bomb[i].Draw(hdc);
		}
	}

	for (int i = 0; i<20; i++)
	{
		if (true == ExplosionCenter[i].flag)
		{
			ExplosionCenter[i].Draw(hdc);

			if (ExplosionCenter[i].m_Index == 2)
			{
				ExplosionCenter[i].flag = false;
			}
		}
	}

	Player_1.Draw(hdc);																				//Player1 그림


	return 0;
}


int KGame::LoadBit(void)
{
	extern HINSTANCE hInst;																			//Inst 핸들 외부에서 불러옴
	m_hBackBit = KDC::OpenImageFromRC(hInst,IDB_BITMAP1);											//배경 맵 이미지 로드

	m_hPlayer_1 = KDC::OpenImageFromRC(hInst,IDB_BITMAP2);											//Player1 이미지 로드
	Player_1.m_hBitmap = m_hPlayer_1;																//Player_1객체에 비트맵 핸들을 전해줌
	Player_1.IniAction(MY_W,MY_H,0);																//액션 초기화, 0번타입
	Player_1.AddAction(0,0,8);																		//Down
	Player_1.AddAction(1,8,8);																		//Up
	Player_1.AddAction(2,16,8);																		//Left
	Player_1.AddAction(3,24,5);																		//Right

	m_hExplosionCenter = KDC::OpenImageFromRC(hInst,IDB_BITMAP5);
	m_hExplosionUp = KDC::OpenImageFromRC(hInst,IDB_BITMAP6);
	m_hExplosionUpEX = KDC::OpenImageFromRC(hInst,IDB_BITMAP7);

	for (int i = 0; i<20; i++)
	{
		ExplosionCenter[i].m_hBitmap = m_hExplosionCenter;
		ExplosionCenter[i].IniAction(ExplosionCenter[i].m_W,ExplosionCenter[i].m_H,0);
		ExplosionCenter[i].AddAction(0,0,3);

		ExplosionUp[i].m_hBitmap = m_hExplosionUp;
		ExplosionUp[i].IniAction(ExplosionUp[i].m_W,ExplosionUp[i].m_H,0);
		ExplosionUp[i].AddAction(0,0,3);
		ExplosionUpEX[i].m_hBitmap = m_hExplosionUpEX;
		ExplosionUpEX[i].IniAction(ExplosionUpEX[i].m_W,ExplosionUpEX[i].m_H,0);
		ExplosionUpEX[i].AddAction(0,0,3);
	}

	m_hBomb = KDC::OpenImageFromRC(hInst,IDB_BITMAP3);												//폭탄 사진 로드
	Player_1.LoadhBomb(m_hBomb);

	return 0;
}

int KGame::Move(void)
{
	if (-1 != mKeyboard.FindKey('R'))																//위로 이동키가 눌려있다면
	{
		Player_1.RunAction(1,1);
		Player_1.MoveUp(m_Map);																		//위로 이동
	}
	if (-1 != mKeyboard.FindKey('F'))																//아래로 이동키가 눌려있다면
	{
		Player_1.RunAction(0,1);
		Player_1.MoveDown(m_Map);																	//아래로 이동
	}
	if (-1 != mKeyboard.FindKey('D'))																//왼쪽으로 이동키가 눌려있다면
	{
		Player_1.RunAction(2,1);
		Player_1.MoveLeft(m_Map);																	//왼쪽으로 이동
	}
	if (-1 != mKeyboard.FindKey('G'))																//오른쪽으로 이동키가 눌려있다면
	{
		Player_1.RunAction(3,1);
		Player_1.MoveRight(m_Map);																	//오른쪽으로 이동
	}
	if (-1 != mKeyboard.FindKey(VK_SHIFT))															//폭탄설치 키가 눌려있다면
	{
		Player_1.SetBomb(m_Map,m_hBomb);															//폭탄설치
	}

	Player_1.SetFocus();																			//Player_1의 타일좌표 잡음
	return 0;
}


int KGame::LoadMap(char * filename)																	//맵 정보 텍스트 파일 불러옴
{
	ifstream fin(filename);

	for (int y = 0; y<13; y++)
	{
		for (int x = 0; x<15; x++)
		{
			fin >> m_Map[y][x];
		}
	}

	return 0;
}


int KGame::CountBomb(void)																			//폭탄 카운트
{
	for (int i = 0; i<Player_1.m_MaxBomb; i++)															
	{
		if (0 < Player_1.m_Bomb[i].m_Life)															//만약 살아있는 폭탄이라면
		{
			Player_1.m_Bomb[i].m_Life--;															//시간초 1 --
			Player_1.m_Bomb[i].RunAction(0,1);

			if (1 == Player_1.m_Bomb[i].m_Life)														//폭탄 라이프가 1이라면
			{
				Explosion(i);																	//폭발
				m_Map[Player_1.m_Bomb[i].m_Y/Player_1.m_H][Player_1.m_Bomb[i].m_X/Player_1.m_W] = 0;//폭탄 죽음
				Player_1.m_Bomb[i].m_Index = 0;
				Player_1.m_Bomb[i].m_Life--;
			}
		}
	}
	return 0;
}


int KGame::Explosion(int index)
{
	for (int i = 0; i<20; i++)																			//중앙
	{
		if (false == ExplosionCenter[i].flag)
		{
			ExplosionCenter[i].flag = true;
			ExplosionCenter[i].m_X = Player_1.m_Bomb[index].m_X;
			ExplosionCenter[i].m_Y = Player_1.m_Bomb[index].m_Y;

			if ((Player_1.m_X == ExplosionCenter[i].m_X) && (Player_1.m_Y == ExplosionCenter[i].m_Y))
			{
				///////////죽음
			}

			ExplosionCenter[i].RunAction(0,2);
			break;
		}
	}

	for (int i = 1; i<=Player_1.m_MaxPower;i++)
	{

	}
	for (int i = 1; i<=Player_1.m_MaxPower;i++)
	{

	}
	for (int i = 1; i<=Player_1.m_MaxPower;i++)
	{

	}
	for (int i = 1; i<=Player_1.m_MaxPower;i++)
	{

	}
	return 0;
}


int KGame::NextFrame(void)
{
	Player_1.NextFrame();
	
	for (int i = 0; i<20; i++)
	{
		if (i <10)
		{
			if (0 < Player_1.m_Bomb[i].m_Life)
			{
				Player_1.m_Bomb[i].NextFrame();
			}
		}
		
		ExplosionCenter[i].NextFrame();
	}

	return 0;
}
