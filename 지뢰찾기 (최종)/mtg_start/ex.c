#include <stdlib.h>
#include <time.h>
#include "mtg.h"
  
#define MY_LEFT 75
#define MY_RIGHT 77
#define MY_UP 72
#define MY_DOWN 80
#define ESC 27
#define SPACE 32

// 게임 환경 변수
#define MAX_DDONG       100 // 똥의 최대 개수.
#define LEVEL_COUNT     3   // 레벨마다 늘어날 똥개수
#define LEVEL_SPEED     15  // 레벨마다 빨라질 스피드 (1000 = 1초, 15 = 0.015초)
 
char g_key=0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//자료구조
int g_level=1; //Input 키 설정할때 쓰임
int g_a=0; // 로고에서 손가락그림 시 사용됨

//떨어지는 단어
struct S_H             //구조체 선언 Heart
{
	int x;
	int y;         
	int life;          //살아있는지
	char msg[10];      //모양
};

struct S_G            //구조체 선언 졸라맨
{
	int x;
	int y;
	int life;
};

struct S_H g_aH[10];
struct S_G g_G; 


int MyCheck()           //하트와 졸라맨 충돌체크
{
	int hi;             //하트 반복변수
	int gi;             //졸라맨 반복변수
	
	for(hi=0;hi<20;hi++)
	{
		if(1 == g_aH[hi].life)
		{
			for(gi=0;gi<10;gi++)
			{
				if(1 == g_G.life)
				{
					if(g_G.y == g_G.y)                                    //y축이 같아야 일단 총알에 맞는다
					{
						if(g_G.x <= g_aH[hi].x && g_aH[hi].x <= g_aH[gi].x+3)  //만약에 총알에 x좌표가 적의 x좌표 범위안에 들어오면 그니까 @__@ 이렇게 생겼으니까 +3까지 범위를 잡음
						{
							g_aH[hi].life=0;                                        //적을 없앰 Draw가보면 life가 1일때만 그려줌
							g_G.life=0;                                       //이거도

							return 1;                                               //함수 끝남  더이상 반복문 돌면 메모리낭비니까 
						}
					}
				}
			}
		}
	}

	return 0;
}




//점수
int g_score=0; 

//////////////////////////////////////////////////////////////////


//남은시간

int g_time1=20;

//////////////////////////////////////////////////////////////////

////로고만들기
int Mystart()
{
	int i;
	int x,y;


	for(i=0;i<10;i++)
	{
		g_aH[i].x=6*i;            //6칸씩 배열
		g_aH[i].y=1;              //첫번째 칸 그니까 맨 위에 적들 배열
		sprintf(g_aH[i].msg,"♥");   //적의 모양 입력
	}


	//gun 초기화

	g_G.x=40;
	g_G.y=20;

	
	 	

 for(y=0;y<=24;y++)
 {
  for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,0,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
   
   _Delay(50);
  }
    for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,1,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,2,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,3,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);   
   
   _Delay(50);
  }
	for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,4,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,5,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,6,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,7,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,8,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,9,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,10,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,11,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,12,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,13,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,14,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,15,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,16,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,17,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,18,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,19,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,20,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,21,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,22,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,23,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,24,"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□",15);
      
   _Delay(50);
  }
   break;
  
  _Delay(50);
 }

 for(y=0;y<=12;y++)
 {
  for(x=0;x<79;x++)
  {
   _DrawTextOrg(x,12-y," ");
   _DrawTextOrg(x,12+y," ");
  }
  _Delay(50);
  }

 _Delay(50);


 /////////////////////////////// 졸라맨♡피하기 게임타이틀 찍기
	

	for(y=0;y<=24;y++)
	{
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,0,"      ■■■■■■                                                              ",14);

		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,1,"          ■■                        ■                      ■  ■            ",14);
	
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,2,"        ■    ■        ■■■■■■  ■        ■■■■■■  ■  ■            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,3,"      ■  ■■  ■                ■  ■        ■        ■  ■■■            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,4,"      ■■■■■■      ■■■■■■  ■■■    ■        ■  ■■■            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,5,"      ■■■■■■      ■            ■        ■■■■■■  ■  ■            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,6,"                ■      ■■■■■■  ■                      ■  ■            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,7,"      ■■■■■■                    ■             ■                         ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,8,"      ■                                             ■■■■■■■■           ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,9,"      ■■■■■■                                                              ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,10,"                                ■      ■                                      ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,11,"                              ■■■  ■■■                                    ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,12,"                            ■■■■■■■■■                                  ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,13,"                              ■■■■■■■                                    ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,14,"                                ■■■■■                                      ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,15,"                                  ■■■                                        ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,16,"                                    ■                                          ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,17,"                    ■          ■■■■    ■                        ■        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,18,"       ■■■■■■ ■        ■■■■■■  ■          ■■■■■■  ■        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,19,"          ■  ■    ■            ■■      ■■■              ■    ■        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,20,"          ■  ■    ■          ■    ■    ■                ■      ■        ",10);
		
		_Delay(100);
	}
	{
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,21,"          ■  ■    ■        ■        ■  ■              ■        ■        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,22,"       ■■■■■■ ■          ■    ■    ■            ■          ■        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,23,"                    ■            ■■      ■           ■           ■        ",10);
		
		_Delay(100);
	}
	
	break;
	}

  _Delay(500);
 

 return 0;
 }
}


// 메인
int MyDraw1() 
{
	char temp[20];

	_DrawText(0,0,"○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●");
	_DrawText(0,1,"●                                                                            ○");
	_DrawText(0,2,"○       ■■  ■■                   ■      ■     ■                ■     ●");
	_DrawText(0,3,"●     ■□□■□□■      ■■■■■ ■  ■■■■■ ■     ■■■■■ ■     ○");
	_DrawText(0,4,"○      ■□□□□■         ■  ■   ■      ■     ■            ■  ■     ●");
	_DrawText(0,5,"●       ■□□□■          ■  ■   ■    ■  ■   ■■■      ■    ■     ○");
	_DrawText(0,6,"○        ■□□■         ■■■■■ ■      ■     ■        ■      ■     ●");
	_DrawText(0,7,"●          ■■                      ■             ■                ■     ○");
	_DrawText(0,8,"○                                                                            ●");
	_DrawText(0,9,"●                             <<  S T A R T  >>                              ○");
	_DrawText(0,10,"○                             <<  줄  거  리 >>                              ●");
	_DrawText(0,11,"●                             <<  도  움  말 >>                              ○");
	_DrawText(0,12,"○                             <<  E  X  I  T >>                              ●");
	_DrawText(0,13,"●                                                                            ○");
	_DrawText(0,14,"○                                                                            ●");
	_DrawText(0,15,"●                                                                            ○");
	_DrawText(0,16,"○     ┌────┐       ♡     ♡     ♡     ♡                             ●");
	_DrawText(0,17,"●     │ 학  교 │         ♡     ♡     ♡     ♡                           ○");
	_DrawText(0,18,"○     └─┐┌─┘       ♡     ♡     ♡     ♡                             ●");
	_DrawText(0,19,"●       ┌┴┴┐           ♡     ♡     ♡     ♡                           ○");
	_DrawText(0,20,"○   ┌─┘    └─┐     ♡     ♡     ♡     ♡          ∩∩               ●");
	_DrawText(0,21,"●   │            │    ↖◎↗ ↖◎↗ ↖◎↗ ↖◎↗     （ºº）             ○");
	_DrawText(0,22,"○   │            │      ▩     ▩     ▩     ▩        ┌▩┘              ●");
	_DrawText(0,23,"●   └──────┘     @ @    @ @    @ @    @ @         ┘┘               ○");
	_DrawText(0,24,"○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●");

	_DrawTextColor(29,9 + g_a * 1,"☞",10);
	_DrawTextColor(48,9 + g_a * 1,"☜",10);
	 
 
	 //남은시간 찍기
	
	

	sprintf(temp,"남은시간 : %d",g_time1);
	_DrawText(60,10,temp);

	 return 0;
}
///////////////////타이머 생성하기
int MyTimer1()
{
	static long oldT1;
	long newT1;

	if(g_level == 1)
	{
		newT1=_GetTickCount();
		if(1000 <= (newT1-oldT1))
		{
			oldT1=newT1;
			g_time1--;
			
			if(g_time1 <= 0)
			{
				g_time1 = 0;
				g_level = 2;
			}

			_Invalidate();
		}
	}

	return 0;
}

/////////////////
int MyInput1(char key)
{
	int y=0;

	if(SPACE == key)
	{
		if(g_a == 0)
		{
			g_level = 5;
		}
		else
		{
			g_level = 1+ g_a;
		}
	}
	else if(MY_UP == key)
	{
		if(g_a >0)
		{
			g_a--;
		}
	}
	else if(MY_DOWN == key)
	{
		if(g_a < 3)
		{
			g_a++;
		}
	}

	_Invalidate();

	
	return 0;
}


/////////////////////////////////////////////////

// 줄거리
int MyDraw2()
{
	_DrawTextColor(0,3,"                               ★  줄 거 리 ★",12);
	_DrawTextColor(0,5,"                               내 이름은 졸라맨.",11);
    _DrawTextColor(0,7,"                     졸라고등학교에 새롭게 전학을 온 졸라맨.",11);
	_DrawTextColor(0,9,"                  중학교까지 철없이 질풍노도기를 보내왔지만.",11);
	_DrawTextColor(0,11,"               전학 온 졸라고에서는 학업에 열중하기로 다짐 하지만",11);
	_DrawTextColor(0,13,"              졸라맨의 너무 잘생긴 외모 탓에 여자들의 하트 세례를 받지.",11);
	_DrawTextColor(0,15,"                               오늘도 내일도...",11);
	_DrawTextColor(0,17,"               어머니~~ 저를 왜 이렇게 잘생기게 낳으신건가요..!!ㅠ_ㅠ",11);
	_DrawTextColor(0,19,"                          제발 누가 나좀 도와줘~~~~~!",11);

	return 0;
}

int MyInput2(char key)
{
	if(SPACE == key)
	{
		g_level = 1;
	}
	_Invalidate();

	return 0;
}

////////////////////////////////////////////////

// 도움말
int MyDraw3()
{
	
	_DrawText(0,0,"○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●");
	_DrawText(0,1,"●                                                                            ○");
	_DrawText(0,2,"○                                                                            ●");
	_DrawText(0,3,"●                                                                            ○");
	_DrawText(0,4,"○                                                                            ●");
	_DrawText(0,5,"●                                                                            ○");
	_DrawText(0,6,"○                                                                            ●");
	_DrawText(0,7,"●                                                                            ○");
	_DrawText(0,8,"○                                                                            ●");
	_DrawText(0,9,"●                                                                            ○");
	_DrawText(0,10,"○                                                                            ●");
	_DrawText(0,11,"●                                                                            ○");
	_DrawText(0,12,"○                                                                            ●");
	_DrawText(0,13,"●                                                                            ○");
	_DrawText(0,14,"○                                                                            ●");
	_DrawText(0,15,"●                                                                            ○");
	_DrawText(0,16,"○                                                                            ●");
	_DrawText(0,17,"●                                                                            ○");
	_DrawText(0,18,"○                                                                            ●");
	_DrawText(0,19,"●                                                                            ○");
	_DrawText(0,20,"○                                                                            ●");
	_DrawText(0,21,"●                                                                            ○");
	_DrawText(0,22,"○                                                                            ●");
	_DrawText(0,23,"●                                                                            ○");
	_DrawText(0,24,"○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●○●");

	return 0;
	
}
int MyInput3(char key)
{
	if(SPACE == key)
	{
		g_level = 1;
	}
	_Invalidate();

	return 0;
}


// exit
int MyDraw4()
{
	_DrawText(10,5,"게임종료");

	
	return 0;
}


// 게임화면
int MyDraw5()
{
	int i;
	
	

	//적 그리기

	for(i=0;i<10;i++)
	{
		if(1 == g_aH[i].life)                            //살아있는것만 그려줌
		{
			_DrawText(g_aH[i].x,g_aH[i].y,g_aH[i].msg);  //구조체의 장점을 알 수 있는 라인 잘 보셈
		}
	}
	
	/////졸라맨그리기
	_DrawText(g_G.x,g_G.y,"★");


	////점수 찍기
	//sprintf(temp, "score:%d", g_score);
	//_DrawText(70,2,temp);
	//
	

	
	return 0;
}

int MyInput5(char key)
{
	int i;

	if(MY_LEFT == key)                 //왼쪽으로 이동
	{
		g_G.x--;
	}
	else if(MY_RIGHT == key)         //오른쪽으로 이동
	{
		g_G.x++;
	}

	_Invalidate();

	return 0;
} 

// 타이머
int MyTimer2()                 //적들이 내려오게 하는 타이머
{
	static long oldT1=0;      //이거 저번에 내가 주석달아서 올림
	long newT1;
	int i;

	newT1=_GetTickCount();

	if(100 <= (newT1-oldT1))
	{
		oldT1=newT1;

		for(i=0;i<10;i++)
		{

			if(1 == g_aH[i].life)         //만약 적이 살아있으면
			{
				g_aH[i].y++;              //한칸씩 내려온다

				if(20 <= g_aH[i].y)       //15칸 내려오면
				{
					g_aH[i].y=0;        //초기화
				}
			}
		}
		_Invalidate();
	}
	return 0;
}

int MyTimer3()
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(1000 <= (newT-oldT))
	{
		oldT=newT;

		g_aH[rand()%10].life=1;

		_Invalidate();
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw()
{
   char temp[20];

   sprintf(temp,"key:%d",g_key);
   _DrawText(70,5,temp);


   if(g_level == 1) //메인
   {
	   MyDraw1();
   }
   else if(g_level == 2) // 줄거리
   {
	   MyDraw2();
   }
   else if(g_level == 3) // 도움말
   {
	   MyDraw3();
   }
   else if(g_level == 4) // exit
   {
	   MyDraw4();
   }
   else if(g_level == 5) // 게임화면
   {
	   MyDraw5();
   }
 /* else if(g_level == 5)
   {
	   MyDraw6();
   }
    else if(g_level == 5)
   {
	   MyDraw7();
   }
	 else if(g_level == 5)
   {
	   MyDraw8();
   }
	 else if(g_level == 5)
   {
	   MyDraw9();
   }
	  else if(g_level == 5)
   {
	   MyDraw9();
   }
	  else if(g_level == 5)
   {
	   MyDraw9();
   }
   */


}

void RunStart()
{
	Mystart();

	_Invalidate();
}

void RunKey(char key)
{
	g_key=key;

	_Invalidate();

	if(g_level==1)
	{
		MyInput1(key);
	}
	else if(g_level==2)
	{
		MyInput2(key);
	}
	else if(g_level==3)
	{
		MyInput3(key);
	}
	 else if(g_level==5)
	{
		MyInput5(key);
	}
	/*
	else if(g_level==6)
	{
		Myinput6(key);
	}
	else if(g_level==7)
	{
		Myinput7(key);
	}
	else if(g_level==8)
	{
		Myinput8(key);
	}
	*/
}

void GameMain()
{
	char key;

	RunStart();

	while(1)
	{
		MyTimer1();
		MyTimer2();
		MyTimer3();
		key=_GetKey();

		if(-1==key) continue;
		if('q'==key) 
		{
			break;
		}

		RunKey(key);
	}
}

int main(void)
{
	_BeginWindow();

	GameMain();

	_EndWindow();


	return 0;
}

