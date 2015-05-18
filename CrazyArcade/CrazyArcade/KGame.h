#pragma once

//#include "resource.h"
#include "KDC.h"
#include "KKeyboard.h"
#include "KMedia.h"
#include "KPlayer.h"
#include "KExplosion.h"

#define MY_W 70
#define MY_H 70

class KGame
{
public:
	KGame(void);
	~KGame(void);

	HBITMAP m_hBackBit;
	
	int Draw(HDC hdc);
	int LoadBit(void);
	
	KKeyboard mKeyboard;
	
	KPlayer Player_1;
	HBITMAP m_hPlayer_1;
	KPlayer Player_2;
	HBITMAP m_hPlayer_2;
	
	HBITMAP m_hBomb;
	
	HBITMAP m_hExplosionCenter;
	
	HBITMAP m_hExplosionUp;
	HBITMAP m_hExplosionUpEX;

	HBITMAP m_hExplosionDown;
	HBITMAP m_hExplosionDownEX;

	HBITMAP m_hExplosionLeft;
	HBITMAP m_hExplosionLeftEX;

	HBITMAP m_hExplosionRight;
	HBITMAP m_hExplosionRightEX;

	KExplosion ExplosionCenter[20];				//IDB_BITMAP5

	KExplosion ExplosionUp[20];					//IDB_BITMAP6
	KExplosion ExplosionUpEX[20];				//IDB_BITMAP7
	
	KExplosion ExplosionDown[20];				//IDB_BITMAP8
	KExplosion ExplosionDownEX[20];				//IDB_BITMAP9

	KExplosion ExplosionLeft[20];				//IDB_BITMAP10
	KExplosion ExplosionLeftEX[20];				//IDB_BITMAP11

	KExplosion ExplosionRight[20];				//IDB_BITMAP12
	KExplosion ExplosionRightEX[20];			//IDB_BITMAP13

	int Move(void);
	int LoadMap(char * filename);
	int m_Map[13][15];
	int CountBomb(void);
	int Explosion(int index);
	int NextFrame(void);
};

