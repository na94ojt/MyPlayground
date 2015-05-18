#include "stdafx.h"
#include "resource.h"
#include "KGame.h"

#include <fstream>

using namespace std;

KGame::KGame(void)
{
	LoadMap("Map1.txt");																			//�� �ε�
	
}


KGame::~KGame(void)
{
}


int KGame::Draw(HDC hdc)
{
	KDC::DrawBitMap(hdc,0,0,MY_W*15,MY_H*13,m_hBackBit,0,0,MY_W*15,MY_H*13);						//���� �׸�

	for (int i = 0; i<Player_1.m_MaxBomb; i++)
	{
		//��ź �׸�
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

	Player_1.Draw(hdc);																				//Player1 �׸�


	return 0;
}


int KGame::LoadBit(void)
{
	extern HINSTANCE hInst;																			//Inst �ڵ� �ܺο��� �ҷ���
	m_hBackBit = KDC::OpenImageFromRC(hInst,IDB_BITMAP1);											//��� �� �̹��� �ε�

	m_hPlayer_1 = KDC::OpenImageFromRC(hInst,IDB_BITMAP2);											//Player1 �̹��� �ε�
	Player_1.m_hBitmap = m_hPlayer_1;																//Player_1��ü�� ��Ʈ�� �ڵ��� ������
	Player_1.IniAction(MY_W,MY_H,0);																//�׼� �ʱ�ȭ, 0��Ÿ��
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

	m_hBomb = KDC::OpenImageFromRC(hInst,IDB_BITMAP3);												//��ź ���� �ε�
	Player_1.LoadhBomb(m_hBomb);

	return 0;
}

int KGame::Move(void)
{
	if (-1 != mKeyboard.FindKey('R'))																//���� �̵�Ű�� �����ִٸ�
	{
		Player_1.RunAction(1,1);
		Player_1.MoveUp(m_Map);																		//���� �̵�
	}
	if (-1 != mKeyboard.FindKey('F'))																//�Ʒ��� �̵�Ű�� �����ִٸ�
	{
		Player_1.RunAction(0,1);
		Player_1.MoveDown(m_Map);																	//�Ʒ��� �̵�
	}
	if (-1 != mKeyboard.FindKey('D'))																//�������� �̵�Ű�� �����ִٸ�
	{
		Player_1.RunAction(2,1);
		Player_1.MoveLeft(m_Map);																	//�������� �̵�
	}
	if (-1 != mKeyboard.FindKey('G'))																//���������� �̵�Ű�� �����ִٸ�
	{
		Player_1.RunAction(3,1);
		Player_1.MoveRight(m_Map);																	//���������� �̵�
	}
	if (-1 != mKeyboard.FindKey(VK_SHIFT))															//��ź��ġ Ű�� �����ִٸ�
	{
		Player_1.SetBomb(m_Map,m_hBomb);															//��ź��ġ
	}

	Player_1.SetFocus();																			//Player_1�� Ÿ����ǥ ����
	return 0;
}


int KGame::LoadMap(char * filename)																	//�� ���� �ؽ�Ʈ ���� �ҷ���
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


int KGame::CountBomb(void)																			//��ź ī��Ʈ
{
	for (int i = 0; i<Player_1.m_MaxBomb; i++)															
	{
		if (0 < Player_1.m_Bomb[i].m_Life)															//���� ����ִ� ��ź�̶��
		{
			Player_1.m_Bomb[i].m_Life--;															//�ð��� 1 --
			Player_1.m_Bomb[i].RunAction(0,1);

			if (1 == Player_1.m_Bomb[i].m_Life)														//��ź �������� 1�̶��
			{
				Explosion(i);																	//����
				m_Map[Player_1.m_Bomb[i].m_Y/Player_1.m_H][Player_1.m_Bomb[i].m_X/Player_1.m_W] = 0;//��ź ����
				Player_1.m_Bomb[i].m_Index = 0;
				Player_1.m_Bomb[i].m_Life--;
			}
		}
	}
	return 0;
}


int KGame::Explosion(int index)
{
	for (int i = 0; i<20; i++)																			//�߾�
	{
		if (false == ExplosionCenter[i].flag)
		{
			ExplosionCenter[i].flag = true;
			ExplosionCenter[i].m_X = Player_1.m_Bomb[index].m_X;
			ExplosionCenter[i].m_Y = Player_1.m_Bomb[index].m_Y;

			if ((Player_1.m_X == ExplosionCenter[i].m_X) && (Player_1.m_Y == ExplosionCenter[i].m_Y))
			{
				///////////����
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
