#include <stdlib.h>
#include <time.h>
#include "mtg.h"
  
#define MY_LEFT 75
#define MY_RIGHT 77
#define MY_UP 72
#define MY_DOWN 80
#define ESC 27
#define SPACE 32

// ���� ȯ�� ����
#define MAX_DDONG       100 // ���� �ִ� ����.
#define LEVEL_COUNT     3   // �������� �þ �˰���
#define LEVEL_SPEED     15  // �������� ������ ���ǵ� (1000 = 1��, 15 = 0.015��)
 
char g_key=0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�ڷᱸ��
int g_level=1; //Input Ű �����Ҷ� ����
int g_a=0; // �ΰ��� �հ����׸� �� ����

//�������� �ܾ�
struct S_H             //����ü ���� Heart
{
	int x;
	int y;         
	int life;          //����ִ���
	char msg[10];      //���
};

struct S_G            //����ü ���� �����
{
	int x;
	int y;
	int life;
};

struct S_H g_aH[10];
struct S_G g_G; 


int MyCheck()           //��Ʈ�� ����� �浹üũ
{
	int hi;             //��Ʈ �ݺ�����
	int gi;             //����� �ݺ�����
	
	for(hi=0;hi<20;hi++)
	{
		if(1 == g_aH[hi].life)
		{
			for(gi=0;gi<10;gi++)
			{
				if(1 == g_G.life)
				{
					if(g_G.y == g_G.y)                                    //y���� ���ƾ� �ϴ� �Ѿ˿� �´´�
					{
						if(g_G.x <= g_aH[hi].x && g_aH[hi].x <= g_aH[gi].x+3)  //���࿡ �Ѿ˿� x��ǥ�� ���� x��ǥ �����ȿ� ������ �״ϱ� @__@ �̷��� �������ϱ� +3���� ������ ����
						{
							g_aH[hi].life=0;                                        //���� ���� Draw������ life�� 1�϶��� �׷���
							g_G.life=0;                                       //�̰ŵ�

							return 1;                                               //�Լ� ����  ���̻� �ݺ��� ���� �޸𸮳���ϱ� 
						}
					}
				}
			}
		}
	}

	return 0;
}




//����
int g_score=0; 

//////////////////////////////////////////////////////////////////


//�����ð�

int g_time1=20;

//////////////////////////////////////////////////////////////////

////�ΰ����
int Mystart()
{
	int i;
	int x,y;


	for(i=0;i<10;i++)
	{
		g_aH[i].x=6*i;            //6ĭ�� �迭
		g_aH[i].y=1;              //ù��° ĭ �״ϱ� �� ���� ���� �迭
		sprintf(g_aH[i].msg,"��");   //���� ��� �Է�
	}


	//gun �ʱ�ȭ

	g_G.x=40;
	g_G.y=20;

	
	 	

 for(y=0;y<=24;y++)
 {
  for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,0,"�����������������������������������������",15);
   
   _Delay(50);
  }
    for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,1,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,2,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,3,"�����������������������������������������",15);   
   
   _Delay(50);
  }
	for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,4,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,5,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,6,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,7,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,8,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,9,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,10,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,11,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,12,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,13,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,14,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,15,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,16,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,17,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,18,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,19,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,20,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,21,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,22,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,23,"�����������������������������������������",15);
      
   _Delay(50);
  }
     for(x=0;x<1;x++)
  {
   _DrawTextColorOrg(0,24,"�����������������������������������������",15);
      
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


 /////////////////////////////// ����Ǣ����ϱ� ����Ÿ��Ʋ ���
	

	for(y=0;y<=24;y++)
	{
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,0,"      �������                                                              ",14);

		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,1,"          ���                        ��                      ��  ��            ",14);
	
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,2,"        ��    ��        �������  ��        �������  ��  ��            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,3,"      ��  ���  ��                ��  ��        ��        ��  ����            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,4,"      �������      �������  ����    ��        ��  ����            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,5,"      �������      ��            ��        �������  ��  ��            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,6,"                ��      �������  ��                      ��  ��            ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,7,"      �������                    ��             ��                         ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,8,"      ��                                             ���������           ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,9,"      �������                                                              ",14);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,10,"                                ��      ��                                      ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,11,"                              ����  ����                                    ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,12,"                            ����������                                  ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,13,"                              ��������                                    ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,14,"                                ������                                      ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,15,"                                  ����                                        ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,16,"                                    ��                                          ",12);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,17,"                    ��          �����    ��                        ��        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,18,"       ������� ��        �������  ��          �������  ��        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,19,"          ��  ��    ��            ���      ����              ��    ��        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,20,"          ��  ��    ��          ��    ��    ��                ��      ��        ",10);
		
		_Delay(100);
	}
	{
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,21,"          ��  ��    ��        ��        ��  ��              ��        ��        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,22,"       ������� ��          ��    ��    ��            ��          ��        ",10);
		
		_Delay(100);
	}
	for(x=0;x<1;x++)
	{
		_DrawTextColorOrg(0,23,"                    ��            ���      ��           ��           ��        ",10);
		
		_Delay(100);
	}
	
	break;
	}

  _Delay(500);
 

 return 0;
 }
}


// ����
int MyDraw1() 
{
	char temp[20];

	_DrawText(0,0,"�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�");
	_DrawText(0,1,"��                                                                            ��");
	_DrawText(0,2,"��       ���  ���                   ��      ��     ��                ��     ��");
	_DrawText(0,3,"��     ��������      ������ ��  ������ ��     ������ ��     ��");
	_DrawText(0,4,"��      �������         ��  ��   ��      ��     ��            ��  ��     ��");
	_DrawText(0,5,"��       ������          ��  ��   ��    ��  ��   ����      ��    ��     ��");
	_DrawText(0,6,"��        �����         ������ ��      ��     ��        ��      ��     ��");
	_DrawText(0,7,"��          ���                      ��             ��                ��     ��");
	_DrawText(0,8,"��                                                                            ��");
	_DrawText(0,9,"��                             <<  S T A R T  >>                              ��");
	_DrawText(0,10,"��                             <<  ��  ��  �� >>                              ��");
	_DrawText(0,11,"��                             <<  ��  ��  �� >>                              ��");
	_DrawText(0,12,"��                             <<  E  X  I  T >>                              ��");
	_DrawText(0,13,"��                                                                            ��");
	_DrawText(0,14,"��                                                                            ��");
	_DrawText(0,15,"��                                                                            ��");
	_DrawText(0,16,"��     ������������       ��     ��     ��     ��                             ��");
	_DrawText(0,17,"��     �� ��  �� ��         ��     ��     ��     ��                           ��");
	_DrawText(0,18,"��     ������������       ��     ��     ��     ��                             ��");
	_DrawText(0,19,"��       ��������           ��     ��     ��     ��                           ��");
	_DrawText(0,20,"��   ������    ������     ��     ��     ��     ��          ����               ��");
	_DrawText(0,21,"��   ��            ��    �ءݢ� �ءݢ� �ءݢ� �ءݢ�     ��������             ��");
	_DrawText(0,22,"��   ��            ��      ��     ��     ��     ��        ���̦�              ��");
	_DrawText(0,23,"��   ����������������     @ @    @ @    @ @    @ @         ����               ��");
	_DrawText(0,24,"�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�");

	_DrawTextColor(29,9 + g_a * 1,"��",10);
	_DrawTextColor(48,9 + g_a * 1,"��",10);
	 
 
	 //�����ð� ���
	
	

	sprintf(temp,"�����ð� : %d",g_time1);
	_DrawText(60,10,temp);

	 return 0;
}
///////////////////Ÿ�̸� �����ϱ�
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

// �ٰŸ�
int MyDraw2()
{
	_DrawTextColor(0,3,"                               ��  �� �� �� ��",12);
	_DrawTextColor(0,5,"                               �� �̸��� �����.",11);
    _DrawTextColor(0,7,"                     �������б��� ���Ӱ� ������ �� �����.",11);
	_DrawTextColor(0,9,"                  ���б����� ö���� ��ǳ�뵵�⸦ ����������.",11);
	_DrawTextColor(0,11,"               ���� �� ��������� �о��� �����ϱ�� ���� ������",11);
	_DrawTextColor(0,13,"              ������� �ʹ� �߻��� �ܸ� ſ�� ���ڵ��� ��Ʈ ���ʸ� ����.",11);
	_DrawTextColor(0,15,"                               ���õ� ���ϵ�...",11);
	_DrawTextColor(0,17,"               ��Ӵ�~~ ���� �� �̷��� �߻���� �����Űǰ���..!!��_��",11);
	_DrawTextColor(0,19,"                          ���� ���� ���� ������~~~~~!",11);

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

// ����
int MyDraw3()
{
	
	_DrawText(0,0,"�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�");
	_DrawText(0,1,"��                                                                            ��");
	_DrawText(0,2,"��                                                                            ��");
	_DrawText(0,3,"��                                                                            ��");
	_DrawText(0,4,"��                                                                            ��");
	_DrawText(0,5,"��                                                                            ��");
	_DrawText(0,6,"��                                                                            ��");
	_DrawText(0,7,"��                                                                            ��");
	_DrawText(0,8,"��                                                                            ��");
	_DrawText(0,9,"��                                                                            ��");
	_DrawText(0,10,"��                                                                            ��");
	_DrawText(0,11,"��                                                                            ��");
	_DrawText(0,12,"��                                                                            ��");
	_DrawText(0,13,"��                                                                            ��");
	_DrawText(0,14,"��                                                                            ��");
	_DrawText(0,15,"��                                                                            ��");
	_DrawText(0,16,"��                                                                            ��");
	_DrawText(0,17,"��                                                                            ��");
	_DrawText(0,18,"��                                                                            ��");
	_DrawText(0,19,"��                                                                            ��");
	_DrawText(0,20,"��                                                                            ��");
	_DrawText(0,21,"��                                                                            ��");
	_DrawText(0,22,"��                                                                            ��");
	_DrawText(0,23,"��                                                                            ��");
	_DrawText(0,24,"�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�");

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
	_DrawText(10,5,"��������");

	
	return 0;
}


// ����ȭ��
int MyDraw5()
{
	int i;
	
	

	//�� �׸���

	for(i=0;i<10;i++)
	{
		if(1 == g_aH[i].life)                            //����ִ°͸� �׷���
		{
			_DrawText(g_aH[i].x,g_aH[i].y,g_aH[i].msg);  //����ü�� ������ �� �� �ִ� ���� �� ����
		}
	}
	
	/////����Ǳ׸���
	_DrawText(g_G.x,g_G.y,"��");


	////���� ���
	//sprintf(temp, "score:%d", g_score);
	//_DrawText(70,2,temp);
	//
	

	
	return 0;
}

int MyInput5(char key)
{
	int i;

	if(MY_LEFT == key)                 //�������� �̵�
	{
		g_G.x--;
	}
	else if(MY_RIGHT == key)         //���������� �̵�
	{
		g_G.x++;
	}

	_Invalidate();

	return 0;
} 

// Ÿ�̸�
int MyTimer2()                 //������ �������� �ϴ� Ÿ�̸�
{
	static long oldT1=0;      //�̰� ������ ���� �ּ��޾Ƽ� �ø�
	long newT1;
	int i;

	newT1=_GetTickCount();

	if(100 <= (newT1-oldT1))
	{
		oldT1=newT1;

		for(i=0;i<10;i++)
		{

			if(1 == g_aH[i].life)         //���� ���� ���������
			{
				g_aH[i].y++;              //��ĭ�� �����´�

				if(20 <= g_aH[i].y)       //15ĭ ��������
				{
					g_aH[i].y=0;        //�ʱ�ȭ
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


   if(g_level == 1) //����
   {
	   MyDraw1();
   }
   else if(g_level == 2) // �ٰŸ�
   {
	   MyDraw2();
   }
   else if(g_level == 3) // ����
   {
	   MyDraw3();
   }
   else if(g_level == 4) // exit
   {
	   MyDraw4();
   }
   else if(g_level == 5) // ����ȭ��
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

