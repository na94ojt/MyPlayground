#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"È°½î±â.h"

void Draw();
void TitleDraw();
void CharDraw();
void GageDraw();
void ArrowDraw();
void Input();

int gage=0;
int state=0;

int main()
{
	while(1)
	{
		Draw();
		Sleep(30);
		Input();
	}

	return 0;
}

void Draw()
{
	TitleDraw();
	CharDraw();
	GageDraw();
}

void TitleDraw()
{
	_DrawText(23,2,"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");
	_DrawText(23,3,"¦¢                                  ¦¢");
	_DrawText(23,4,"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
	_DrawText(30,3,"Àç¹ÌÀÖ´Â È°½î±â °ÔÀÓ!!!");
}

void CharDraw()
{
	_DrawText(5,15," O¢Ø");
	_DrawText(5,16," l-¢Õ¡æ");
	_DrawText(5,17,"¡ó¢×");
}

void GageDraw()
{
	int i;

	_DrawText(30,20,"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");
	_DrawText(30,21,"¦¢                    ¦¢");
	_DrawText(30,22,"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");

	for(i=0;i<gage;i++)
	{
		_DrawText(32+i,21,"l");
	}

	if(state == 0 && gage > 0)
	{
		ArrowDraw();
	}
}

void Input()
{
	if((GetAsyncKeyState(VK_SPACE)&0x8000 || GetAsyncKeyState(VK_SPACE)&0x8001) && gage < 20)
	{
		state=1;
		gage++;
	}
	else if((GetAsyncKeyState(VK_SPACE)&0x8000 || GetAsyncKeyState(VK_SPACE)&0x8001) && gage >= 20)
	{
		gage=0;
	}
	else
	{
		state=0;
	}
}

void ArrowDraw()
{
	int i;
	char temp[10];
	for(i=10;i<gage*3;i++)
	{

		_DrawText(i,16,"¡æ");

		Sleep(50);

		_DrawText(i,16," ");
	}

	_DrawText(i,17,"¢Ù");
	sprintf(temp,"%dM",gage*20);
	_DrawText(i,18,temp);

	system("PAUSE>NUL");
	
	_DrawText(i,17," ");
	_DrawText(i,18,"    ");

	gage=0;

}