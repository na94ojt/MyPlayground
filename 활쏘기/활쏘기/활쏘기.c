#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"�偷豏�.h"

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
	_DrawText(23,2,"忙式式式式式式式式式式式式式式式式式忖");
	_DrawText(23,3,"弛                                  弛");
	_DrawText(23,4,"戌式式式式式式式式式式式式式式式式式戎");
	_DrawText(30,3,"營嘐氈朝 �偷豏� 啪歜!!!");
}

void CharDraw()
{
	_DrawText(5,15," OＪ");
	_DrawText(5,16," l-Ｇ⊥");
	_DrawText(5,17,"☉Ｉ");
}

void GageDraw()
{
	int i;

	_DrawText(30,20,"忙式式式式式式式式式式忖");
	_DrawText(30,21,"弛                    弛");
	_DrawText(30,22,"戌式式式式式式式式式式戎");

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

		_DrawText(i,16,"⊥");

		Sleep(50);

		_DrawText(i,16," ");
	}

	_DrawText(i,17,"Ｋ");
	sprintf(temp,"%dM",gage*20);
	_DrawText(i,18,temp);

	system("PAUSE>NUL");
	
	_DrawText(i,17," ");
	_DrawText(i,18,"    ");

	gage=0;

}