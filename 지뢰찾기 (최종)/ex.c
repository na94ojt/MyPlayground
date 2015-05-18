
#include <stdlib.h>
#include <time.h>
#include "mtg.h"
  
#define MY_LEFT 75
#define MY_RIGHT 77
#define MY_UP 72
#define MY_DOWN 80
#define MY_ENTER 13
#define MY_SPACE 32
 
char g_key=0;

/////////////////////////////////////////////////////////// 전역 변수들

int g_stage=0;            //0은 메인 1은 게임설명 2는 게임 종료 3은 난이도 선택 4는 쉬움 5는 어려움
int g_select=3;
int g_Infor=0;
int g_InforCount=0;
int g_x=0;
int g_y=0;
int g_Gameover=0;
int g_EasyBomb=0;
int g_HardBomb=0;
int g_EasyTime=0;
int g_HardTime=0;

int orgcolor=0;

/////////////////////////////////////////////////////////// 배열들

int g_title[25][40]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
		{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
int g_EasyField[2][12][12];
int g_HardField[2][22][22];

/////////////////////////////////////////////////////////// 원일용 교수님께서 미리 만들어주신 함수들 원형
void Draw();
void RunStart();
void RunKey(char key);
void GameMain();

/////////////////////////////////////////////////////////// 내가 만든 함수들 원형

int MyOpening();
int MyDraw();
int MyInput(char key);
int MainDraw();
int MainInput(char key);
int InforDraw();
int InforInput(char key);
int InforCount();
int LevelChoiceDraw();
int LevelChoiceInput(char key);

//
int EasyField();
int EasyDraw();
int EasyInput(char key);
int EasyBombShow();
int EasyOneshot(int x,int y);
int EasyTimer();
int EasyWin();
//

//
int HardField();
int HardDraw();
int HardInput(char key);
int HardBombShow();
int HardOneshot(int x,int y);
int HardTimer();
int HardWin();
//

////////////////////////////////////////////////////////// 원일용 교수님께서 미리 만들어주신 함수들

int main(void)
{
	_BeginWindow();

	GameMain();

	_EndWindow();


	return 0;
}
void GameMain()
{
	char key;

	RunStart();

	while(1)
	{
		key=_GetKey();

		if(1 == g_stage && (3 == g_Infor || 4 == g_Infor))
		{
			InforCount();
		}
		else if(4 == g_stage)
		{
			EasyTimer();
		}
		else if(5 == g_stage)
		{
			HardTimer();
		}

		if(-1==key) continue;
		if('q'==key) 
		{
			break;
		}

		RunKey(key);
	}
}
void RunStart()
{
	MyOpening();
	EasyField();
	HardField();
	_Invalidate();
}
void RunKey(char key)
{
	g_key=key;

	_Invalidate();

	MyInput(key);

}
void Draw()
{
  MyDraw();
}

////////////////////////////////////////////////////////// 내가 만든 함수들 정의

int MyOpening()
{
	register int n,x,y;

	
	int orgcolor=2;

	x=7;
	y=10;

	for(n=0;n<5;n++)
	{
		
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);
		
		orgcolor++;
		_Delay(50);
	}
	
	for(n=0;n<5;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");
		
		_Delay(50);
	}
	
	x=30;
	y=6;

	for(n=0;n<5;n++)
	{
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor); 
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);
		orgcolor++;
		_Delay(50);
	}

	for(n=0;n<5;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");

		_Delay(50);
	}
	
	x=18;
	y=20;

	for(n=0;n<5;n++)
	{
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor); 
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);

		_Delay(50);
	}

	for(n=0;n<5;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");

		_Delay(50);
	}

	x=35;
	y=20;

	for(n=0;n<5;n++)
	{
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor); 
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);

		_Delay(50);
	}

	for(n=0;n<5;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");

		_Delay(50);
	}

	x=6;
	y=6;

	for(n=0;n<5;n++)
	{
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor); 
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);

		_Delay(50);
	}

	for(n=0;n<5;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");

		_Delay(50);
	}

	

	for(n=0;n<13;n++)
	{
		_DrawTextOrg(40,24-n,"|");
		_Delay(30);
	}

	for(n=0;n<13;n++)
	{
		_DrawTextOrg(40,24-n," ");
		_Delay(30);
	}

	_Delay(500);

	x=19;
	y=12;

	for(n=0;n<20;n++)
	{
		_DrawTextColorOrg((x-n)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y-n,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y-n,"■",orgcolor); 
		_DrawTextColorOrg((x+n)*2,y,"■",orgcolor);
		_DrawTextColorOrg((x+n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y+n,"■",orgcolor);
		_DrawTextColorOrg((x-n)*2,y,"■",orgcolor);

		_Delay(50);
	}

	for(n=0;n<20;n++)
	{
		_DrawTextOrg((x-n)*2,y-n,"  ");
		_DrawTextOrg((x)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y-n,"  ");
		_DrawTextOrg((x+n)*2,y,"  ");
		_DrawTextOrg((x+n)*2,y+n,"  ");
		_DrawTextOrg((x)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y+n,"  ");
		_DrawTextOrg((x-n)*2,y,"  ");

		_Delay(50);
	}

	for(y=0;y<25;y++)
	{
		for(x=0;x<40;x++)
		{
			_DrawTextColorOrg(rand()%40*2,rand()%25,"■",0xE);
		}
	}
	
	_Delay(10);

	for(y=0;y<25;y++)
	{
		for(x=0;x<40;x++)
		{
			_DrawTextColorOrg(rand()%40*2,rand()%25,"■",0xE);
		}
	}

	_Delay(100);

	for(y=0;y<25;y++)
	{
		for(x=0;x<40;x++)
		{
			_DrawTextColorOrg(x*2,y,"■",0xE);
		}
	}

	_Delay(1000);
	
	for(y=0;y<25;y++)
	{
		for(x=0;x<40;x++)
		{
			if(g_title[10-y][x] == 0)
			{
				_DrawTextColorOrg(x*2,10-y,"□",0x3);
			}
			else if(g_title[10-y][x] == 1)
			{
				_DrawTextColorOrg(x*2,10-y,"■",0xB);
			}
			

			if(g_title[10+y][x] == 0)
			{
				_DrawTextColorOrg(x*2,10+y,"□",0x3);
			}
			else if(g_title[10+y][x] == 1)
			{
				_DrawTextColorOrg(x*2,10+y,"■",0xB);
			}
		}

		_Delay(10);
	}
	return 0;
}
int MyDraw()
{
	switch(g_stage)
	{
	case 0:
		MainDraw();
		break;
	case 1:
		InforDraw();
		break;
	case 2:
		exit(0);
		break;
	case 3:
		LevelChoiceDraw();
		break;
	case 4:
		EasyDraw();
		break;
	case 5:
		HardDraw();
		break;
	default:
		_DrawText(18,10,"예상치 못한 오류가 발견되었습니다. 연락주세요 (010-8207-4297)");
		break;
	}
	return 0;
}
int MyInput(char key)
{
	switch(g_stage)
	{
	case 0:
		MainInput(key);
		break;
	case 1:
		InforInput(key);
		break;
	case 2:
		exit(0);
		break;
	case 3:
		LevelChoiceInput(key);
		break;
	case 4:
		EasyInput(key);
		break;
	case 5:
		HardInput(key);
		break;
	default:
		_DrawText(18,10,"예상치 못한 오류가 발견되었습니다. 연락주세요 (010-8207-4297)");
		break;
	}
	return 0;
}
int MainDraw()
{
	int x,y;

	for(y=0;y<25;y++)
	{
		for(x=0;x<40;x++)
		{
			if(g_title[y][x] == 0)
			{
				_DrawTextColor(x*2,y,"□",15);
			}
			else if(g_title[y][x] == 1)
			{
				_DrawTextColor(x*2,y,"■",0xB);
			}
		}
	}

	_DrawTextColor(28*2,g_select,"▶",0x4);
	_DrawTextColor(29*2,3,"게임시작",0x7);
	_DrawTextColor(29*2,4,"게임설명",0x7);
	_DrawTextColor(29*2,5,"게임끝내기",0x7);
	return 0;
}
int MainInput(char key)
{
	if(MY_UP == key)
	{
		if(3 <= g_select-1 && 5 >= g_select-1)
		{
			g_select--;
			_Invalidate();
		}
	}
	else if(MY_DOWN == key)
	{
		if(3 <= g_select+1 && 5 >= g_select+1)
		{
			g_select++;
			_Invalidate();
		}
	}
	else if(MY_ENTER == key)
	{
		switch(g_select)
		{
		case 3:
			g_stage=3;
			break;
		case 4:
			g_stage=1;
			break;
		case 5:
			g_stage=2;
			break;
		default:
			_DrawText(18,10,"예상치 못한 오류가 발견되었습니다. 연락주세요 (010-8207-4297)");
			break;
		}

		_Invalidate();
	}

	return 0;
}
int InforDraw()
{
	int x,y;
	int arr[5][5]={
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,3,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	};
	
	switch(g_Infor)
	{
	case 0:
		_DrawText(10,12,"『지금부터 지뢰찾기에 대해서 설명드리도록 하겠습니다.』┘Enter");
		break;
	case 1:
		_DrawText(10,17,"『제가 칸 하나를 골라서 Enter를 눌렀더니 3이란 숫자가 나왔네요.");
		_DrawText(10,18,"  이건 과연 무슨 뜻일까요??』┘Enter");

		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
					_DrawText(x*2+35,y+10,"※");
				else if(0 == arr[y][x])
					_DrawText(x*2+35,y+10,"□");
				else
					_DrawText(x*2+35,y+10,"３");
			}
			
		}

		break;
	case 2:
		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
					_DrawText(x*2+35,y+10,"※");
				else if(0 == arr[y][x])
					_DrawText(x*2+35,y+10,"□");
				else
					_DrawText(x*2+35,y+10,"３");
			}
		}

		_DrawText(10,17,"『네 그렇습니다.』┘Enter");

		break;
	case 3:
		if(0 == g_InforCount%2)
		{
			for(y=0;y<5;y++)
			{
				for(x=0;x<5;x++)
				{
					if(1 == arr[y][x])
						_DrawText(x*2+35,y+10,"※");
					else if(0 == arr[y][x])
						_DrawText(x*2+35,y+10,"□");
					else
						_DrawText(x*2+35,y+10,"３");
				}
			}
		}
		else
		{
			for(y=0;y<5;y++)
			{
				for(x=0;x<5;x++)
				{
					if(1 == arr[y][x])
						_DrawText(x*2+35,y+10,"※");
					else if(0 == arr[y][x])
						_DrawText(x*2+35,y+10,"▣");
					else
						_DrawText(x*2+35,y+10,"３");
				}
			}
		}

		_DrawText(10,17,"『지금 깜빡이고 있는 부분중 3곳에 지뢰가 있다는 뜻입니다!!』┘Enter");

		break;

	case 4:
		if(0 == g_InforCount%2)
		{
			for(y=0;y<5;y++)
			{
				for(x=0;x<5;x++)
				{
					if(1 == arr[y][x])
						_DrawText(x*2+35,y+10,"※");
					else if(0 == arr[y][x])
						_DrawText(x*2+35,y+10,"□");
					else
						_DrawText(x*2+35,y+10,"３");
				}
			}
		}
		else
		{
			for(y=0;y<5;y++)
			{
				for(x=0;x<5;x++)
				{
					if(1 == arr[y][x])
						_DrawText(x*2+35,y+10,"※");
					else if(0 == arr[y][x])
						_DrawText(x*2+35,y+10,"▣");
					else
						_DrawText(x*2+35,y+10,"３");
				}
			}
		}

		_DrawText(10,17,"『정말인지 확인해볼까요??』┘Enter");
		break;
	case 5:
		_DrawText(35,10,"※※※※※");
		_DrawText(35,11,"※★★１※");
		_DrawText(35,12,"※２３２※");
		_DrawText(35,13,"※  １★※");
		_DrawText(35,14,"※※※※※");
		
		_DrawText(10,17,"『진짜네요?』┘Enter");

		break;

	case 6:
		_DrawText(35,10,"※※※※※");
		_DrawText(35,11,"※★★１※");
		_DrawText(35,12,"※２３２※");
		_DrawText(35,13,"※  １★※");
		_DrawText(35,14,"※※※※※");
		
		_DrawText(10,17,"『나머지 숫자들은 사람이라면 왜 저런 숫자가 할당되어있는지");
		_DrawText(10,18,"  알 수 있을 것입니다.』┘Enter");

		break;

	case 7:
		_DrawText(10,12,"『이제 여러분은 지뢰찾기에 대한 룰을 이해하신 겁니다.』┘Enter");
		break;
	case 8:
		_DrawText(10,12,"『이제 조작법에 대해 알아보도록 하겠습니다.』┘Enter");
		break;
	case 9:
		_DrawText(10,12,"『Enter키를 누르시면 그 지역을 조사합니다.");
		_DrawText(10,13,"  만약 지뢰라면 게임에서 지겠죠? 한 번 해봅시다.』┘Enter");
		break;
	case 10:
		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}

		_DrawText((g_x+16)*2,g_y+11,"■");

		_DrawText(10,20,"『방향키로 이동하면서 원하는 지역에서 Enter를 누르세요.』");

		break;
	case 11:
		arr[g_y+1][g_x+1]=2;

		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else if(2 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"１");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}

		_DrawText(10,20,"『잘하셨습니다』┘Enter");
		break;
	case 12:
		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}
		_DrawText(10,20,"『이번에는 지뢰표시를 해봅시다.』┘Enter");
		break;
	case 13:
		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}
		_DrawText(10,20,"『지뢰로 의심되는 부분에서 Space Bar를 눌러봅시다.』┘Enter");
		break;
	case 14:
		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}
		_DrawText((g_x+16)*2,g_y+11,"■");
		_DrawText(10,20,"『자! 해보세요!』");
		break;
	case 15:
		arr[g_y+1][g_x+1]=2;

		for(y=0;y<5;y++)
		{
			for(x=0;x<5;x++)
			{
				if(1 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"※");
				}
				else if(2 == arr[y][x])
				{
					_DrawText((x+15)*2,y+10,"▒");
				}
				else
				{
					_DrawText((x+15)*2,y+10,"□");
				}
			}
		}

		_DrawText(10,20,"『잘하셨습니다』┘Enter");
		break;
	case 16:
		_DrawText(10,12,"『이제 여러분은 이 게임에 대해 모든 것을 아실겁니다.』┘Enter");
		break;
	case 17:
		_DrawText(10,12,"『이제 게임을 즐기기만 하시면 됩니다.』┘Enter");
		break;
	case 18:
		_DrawText(10,12,"『건투를 빕니다.』┘Enter");
		break;
	case 19:
		g_x=0;
		g_y=0;
		g_Infor=0;
		g_stage=0;
		_Invalidate();
		break;
	default:
		_DrawText(18,10,"예상치 못한 오류가 발견되었습니다. 연락주세요 (010-8207-4297)");
		break;
	}

	return 0;
}
int InforInput(char key)
{
	if(10 == g_Infor)
	{
		if(MY_UP == key)
		{
			if(g_y>=1)
			{
				g_y--;
				_Invalidate();
			}
		}
		else if(MY_DOWN == key)
		{
			if(g_y+1<3)
			{
				g_y++;
				_Invalidate();
			}
		}
		else if(MY_LEFT == key)
		{
			if(g_x>=1)
			{
				g_x--;
				_Invalidate();
			}
		}
		else if(MY_RIGHT == key)
		{
			if(g_x+1<3)
			{
				g_x++;
				_Invalidate();
			}
		}
		else if(MY_ENTER == key)
		{
			g_Infor++;
			_Invalidate();
		}

	}
	else if(14 == g_Infor)
	{
		if(MY_UP == key)
		{
			if(g_y>=1)
			{
				g_y--;
				_Invalidate();
			}
		}
		else if(MY_DOWN == key)
		{
			if(g_y+1<3)
			{
				g_y++;
				_Invalidate();
			}
		}
		else if(MY_LEFT == key)
		{
			if(g_x>=1)
			{
				g_x--;
				_Invalidate();
			}
		}
		else if(MY_RIGHT == key)
		{
			if(g_x+1<3)
			{
				g_x++;
				_Invalidate();
			}
		}
		else if(MY_SPACE == key)
		{
			g_Infor++;
			_Invalidate();
		}
	}
	else if(MY_ENTER == key)
	{
		g_Infor++;
		_Invalidate();
	}
	return 0;
}
int InforCount()
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(100 <= (newT-oldT))
	{
		oldT=newT;

		g_InforCount++;

		_Invalidate();
	}

	return 0;
}
int LevelChoiceDraw()
{
	_DrawText(30,5,"#난이도를 선택하세요#");
	_DrawText(36,7,"쉬움");
	_DrawText(36,9,"어려움");
	_DrawText(34,g_y+7,"▶");

	return 0;
}
int LevelChoiceInput(char key)
{
	if(MY_DOWN == key)
	{
		if(g_y+2 < 4)
		{
			g_y+=2;
		}
	}
	else if(MY_UP == key)
	{
		if(g_y-2 >= 0)
		{
			g_y-=2;
		}
	}
	else if(MY_ENTER == key)
	{
		switch(g_y)
		{
		case 0:
			g_y=0;
			g_x=0;
			g_stage=4;
			break;
		case 2:
			g_y=0;
			g_x=0;
			g_stage=5;
			break;
		default:
			_DrawText(18,10,"예상치 못한 오류가 발견되었습니다. 연락주세요 (010-8207-4297)");
			break;
		}
	}

	_Invalidate();

	return 0;
}

//
int EasyField()
{
	int x,y,bomb;

	srand(time(NULL));

	for(y=0;y<12;y++)
	{
		for(x=0;x<12;x++)
		{
			g_EasyField[0][y][x]=rand()%10;

			if(x==0 || y==0 || x==11 || y==11)
			{
				g_EasyField[0][y][x]=200;
			}
		}
	}

	for(y=0;y<12;y++)
	{
		for(x=0;x<12;x++)
		{
			bomb=0;

			if(g_EasyField[0][y][x] == 0)
			{
				g_EasyBomb++;
				continue;
			}
			else if(g_EasyField[0][y][x] == 200)
			{
				continue;
			}
			else
			{
				if(g_EasyField[0][y-1][x-1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y][x-1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y+1][x-1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y+1][x] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y+1][x+1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y][x+1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y-1][x+1] == 0)
				{
					bomb++;
				}
				if(g_EasyField[0][y-1][x] == 0)
				{
					bomb++;
				}
			}

			if(bomb == 0)
			{
				g_EasyField[0][y][x]=100;
			}
			else
			{
				g_EasyField[0][y][x]=bomb;
			}
		}
	}


	for(y=0;y<12;y++)
	{
		for(x=0;x<12;x++)
		{
			g_EasyField[1][y][x]=0;
		}
	}

	return 0;
}
int EasyDraw()
{
	int x,y;
	int EasyDraw_bomb=0;
	char temp[100];

	for(y=0;y<12;y++)
	{
		for(x=0;x<12;x++)
		{
			if(g_EasyField[0][y][x] == 200)
			{
				_DrawText((x+10)*2,y+5,"※");
			}
			else if(g_EasyField[1][y][x] == 1)
			{
				if(g_EasyField[0][y][x] == 0)
				{
					_DrawText((x+10)*2,y+5,"★");

					if(g_Gameover == 0)
					{
						EasyBombShow();
					}
				}
				else
				{
					switch(g_EasyField[0][y][x])
					{
					case 1:
						_DrawText((x+10)*2,y+5,"１");
						break;
					case 2:
						_DrawText((x+10)*2,y+5,"２");
						break;
					case 3:
						_DrawText((x+10)*2,y+5,"３");
						break;
					case 4:
						_DrawText((x+10)*2,y+5,"４");
						break;
					case 5:
						_DrawText((x+10)*2,y+5,"５");
						break;
					case 6:
						_DrawText((x+10)*2,y+5,"６");
						break;
					case 7:
						_DrawText((x+10)*2,y+5,"７");
						break;
					case 8:
						_DrawText((x+10)*2,y+5,"８");
						break;
					case 100:
						_DrawText((x+10)*2,y+5,"  ");
						break;
					default:
						break;
					}
				}
			}
			else if(g_EasyField[1][y][x] == 300)
			{
				_DrawText((x+10)*2,y+5,"▒");

				if(g_EasyField[0][y][x] == 0)
				{
					EasyDraw_bomb++;
				}
			}
			else 
			{
				_DrawText((x+10)*2,y+5,"□");
			}
		}
	}
	if(g_EasyBomb == EasyDraw_bomb)
	{
		EasyWin();
	}

	for(x=22;x<27;x++)
	{
		_DrawText(x*2,5,"※");
	}

	for(y=5;y<17;y++)
	{
		_DrawText(x*2,y,"※");
	}

	y--;

	for(x=22;x<27;x++)
	{
		_DrawText(x*2,y,"※");
	}

	for(x=22;x<27;x++)
	{
		_DrawText(x*2,10,"※");
	}
	
	_DrawText(45,6,"경과시간");
	sprintf(temp,"%d",g_EasyTime);
	_DrawText(48,8,temp);

	if(g_Gameover == 1)
	{
		_DrawText(44,13,"*GameOver*");
		_DrawText(44,14,"Wait a minute");
	}
	else
	{
		_DrawText(45,13,"GameStart");
	}

	_DrawText((g_x+11)*2,g_y+6,"■");

	
	return 0;
}
int EasyInput(char key)
{
	if(MY_UP == key)
	{
		if(g_y>0)
		{
			g_y--;
		}
	}
	else if(MY_DOWN == key)
	{
		if(g_y<9)
		{
			g_y++;
		}
	}
	else if(MY_LEFT == key)
	{
		if(g_x>0)
		{
			g_x--;
		}
	}
	else if(MY_RIGHT == key)
	{
		if(g_x<9)
		{
			g_x++;
		}
	}
	else if(MY_ENTER == key)
	{
		if(g_EasyField[0][g_y+1][g_x+1] == 100)
		{
			g_EasyField[1][g_y+1][g_x+1]=1;
			EasyOneshot(g_x+1,g_y+1);
		}
		else
		{
			g_EasyField[1][g_y+1][g_x+1]=1;
		}
	}
	else if(MY_SPACE == key)
	{
		if(g_EasyField[1][g_y+1][g_x+1] ==300)
		{
			g_EasyField[1][g_y+1][g_x+1]=0;
		}
		else
		{
			g_EasyField[1][g_y+1][g_x+1]=300;
		}
	}

	_Invalidate();

	return 0;
}
int EasyBombShow()
{
	int x,y;

	g_Gameover=1;

	for(y=0;y<12;y++)
	{
		for(x=0;x<12;x++)
		{
			if(g_EasyField[0][y][x] == 0)
			{
				g_EasyField[1][y][x]=1;
			}
		}
	}

	_Invalidate();

	_Delay(5000);

	exit(0);

	return 0;
}
int EasyOneshot(int x,int y)
{
	g_EasyField[1][y][x]=1;
	g_EasyField[1][y-1][x-1]=1;
	g_EasyField[1][y-1][x]=1;
	g_EasyField[1][y-1][x+1]=1;
	g_EasyField[1][y][x+1]=1;
	g_EasyField[1][y+1][x+1]=1;
	g_EasyField[1][y+1][x]=1;
	g_EasyField[1][y+1][x-1]=1;
	g_EasyField[1][y][x-1]=1;

	return 0;
}
int EasyTimer()
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(1000 <= (newT-oldT))
	{
		oldT=newT;

		g_EasyTime++;

		_Invalidate();
	}

	return 0;
}
int EasyWin()
{
	_DrawTextOrg(45,13,"GameWin  ");
	_DrawTextOrg(45,14,"Wait a minute");

	_Delay(5000);

	g_select=3;
	g_stage=0;
	g_x=0;
	g_y-0;

	_Invalidate();

	return 0;
}
//

//
int HardField()
{
	int x,y,bomb;

	srand(time(NULL));

	for(y=0;y<22;y++)
	{
		for(x=0;x<22;x++)
		{
			g_HardField[0][y][x]=rand()%10;

			if(x==0 || y==0 || x==21 || y==21)
			{
				g_HardField[0][y][x]=200;
			}
		}
	}

	for(y=0;y<22;y++)
	{
		for(x=0;x<22;x++)
		{
			bomb=0;

			if(g_HardField[0][y][x] == 0)
			{
				g_HardBomb++;
				continue;
			}
			else if(g_HardField[0][y][x] == 200)
			{
				continue;
			}
			else
			{
				if(g_HardField[0][y-1][x-1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y][x-1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y+1][x-1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y+1][x] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y+1][x+1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y][x+1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y-1][x+1] == 0)
				{
					bomb++;
				}
				if(g_HardField[0][y-1][x] == 0)
				{
					bomb++;
				}
			}

			if(bomb == 0)
			{
				g_HardField[0][y][x]=100;
			}
			else
			{
				g_HardField[0][y][x]=bomb;
			}
		}
	}


	for(y=0;y<22;y++)
	{
		for(x=0;x<22;x++)
		{
			g_HardField[1][y][x]=0;
		}
	}

	return 0;
}
int HardDraw()
{
	int x,y;
	int HardDraw_bomb=0;
	char temp[100];

	for(y=0;y<22;y++)
	{
		for(x=0;x<22;x++)
		{
			if(g_HardField[0][y][x] == 200)
			{
				_DrawText(x*2,y,"※");
			}
			else if(g_HardField[1][y][x] == 1)
			{
				if(g_HardField[0][y][x] == 0)
				{
					_DrawText(x*2,y,"★");

					if(g_Gameover == 0)
					{
						HardBombShow();
					}
				}
				else
				{
					switch(g_HardField[0][y][x])
					{
					case 1:
						_DrawText(x*2,y,"１");
						break;
					case 2:
						_DrawText(x*2,y,"２");
						break;
					case 3:
						_DrawText(x*2,y,"３");
						break;
					case 4:
						_DrawText(x*2,y,"４");
						break;
					case 5:
						_DrawText(x*2,y,"５");
						break;
					case 6:
						_DrawText(x*2,y,"６");
						break;
					case 7:
						_DrawText(x*2,y,"７");
						break;
					case 8:
						_DrawText(x*2,y,"８");
						break;
					case 100:
						_DrawText(x*2,y,"  ");
						break;
					default:
						break;
					}
				}
			}
			else if(g_HardField[1][y][x] == 300)
			{
				_DrawText(x*2,y,"▒");

				if(g_HardField[0][y][x] == 0)
				{
					HardDraw_bomb++;
				}
			}
			else 
			{
				_DrawText(x*2,y,"□");
			}
		}
	}
	if(g_HardBomb == HardDraw_bomb)
	{
		HardWin();
	}

	for(x=22;x<27;x++)
	{
		_DrawText(x*2,0,"※");
	}

	for(y=0;y<22;y++)
	{
		_DrawText(x*2,y,"※");
	}


	for(x=22;x<27;x++)
	{
		_DrawText(x*2,21,"※");
	}

	for(x=22;x<27;x++)
	{
		_DrawText(x*2,11,"※");
	}

	_DrawText(45,4,"경과시간");
	sprintf(temp,"%d",g_HardTime);
	_DrawText(48,6,temp);

	if(g_Gameover == 1)
	{
		_DrawText(44,16,"*GameOver*");
		_DrawText(44,17,"Wait a minute");
	}
	else
	{
		_DrawText(45,16,"GameStart");
	}

	_DrawText((g_x+1)*2,g_y+1,"■");

	return 0;
}
int HardInput(char key)
{
	if(MY_UP == key)
	{
		if(g_y>0)
		{
			g_y--;
		}
	}
	else if(MY_DOWN == key)
	{
		if(g_y<19)
		{
			g_y++;
		}
	}
	else if(MY_LEFT == key)
	{
		if(g_x>0)
		{
			g_x--;
		}
	}
	else if(MY_RIGHT == key)
	{
		if(g_x<19)
		{
			g_x++;
		}
	}
	else if(MY_ENTER == key)
	{
		if(g_HardField[0][g_y+1][g_x+1] == 100)
		{
			g_HardField[1][g_y+1][g_x+1]=1;
			HardOneshot(g_x+1,g_y+1);
		}
		else
		{
			g_HardField[1][g_y+1][g_x+1]=1;
		}
	}
	else if(MY_SPACE == key)
	{
		if(g_HardField[1][g_y+1][g_x+1] ==300)
		{
			g_HardField[1][g_y+1][g_x+1]=0;
		}
		else
		{
			g_HardField[1][g_y+1][g_x+1]=300;
		}
	}

	_Invalidate();

	return 0;
}
int HardBombShow()
{
	int x,y;

	g_Gameover=1;

	for(y=0;y<22;y++)
	{
		for(x=0;x<22;x++)
		{
			if(g_HardField[0][y][x] == 0)
			{
				g_HardField[1][y][x]=1;
			}
		}
	}

	_Invalidate();

	_Delay(5000);

	exit(0);

	return 0;
}
int HardOneshot(int x,int y)
{
	g_HardField[1][y][x]=1;
	g_HardField[1][y-1][x-1]=1;
	g_HardField[1][y-1][x]=1;
	g_HardField[1][y-1][x+1]=1;
	g_HardField[1][y][x+1]=1;
	g_HardField[1][y+1][x+1]=1;
	g_HardField[1][y+1][x]=1;
	g_HardField[1][y+1][x-1]=1;
	g_HardField[1][y][x-1]=1;

	return 0;
}
int HardTimer()
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(1000 <= (newT-oldT))
	{
		oldT=newT;

		g_HardTime++;

		_Invalidate();
	}

	return 0;
}
int HardWin()
{
	_DrawTextOrg(45,16,"GameWin  ");
	_DrawTextOrg(45,16,"Wait a minute");

	_Delay(5000);

	g_x=0;
	g_y=0;
	g_stage=0;
	g_select=3;

	_Invalidate();

	return 0;
}
//

/////////////////////////////////////////////////////////////