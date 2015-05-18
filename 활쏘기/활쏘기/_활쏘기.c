#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"È°½î±â.h"

#define GSH GetStdHandle(STD_OUTPUT_HANDLE)

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize=1;
	cursor.bVisible=FALSE;
	SetConsoleCursorInfo(GSH,&cursor);
	SetConsoleCursorPosition(GSH,pos);
}

void _DrawText(int x,int y,char * str)
{
	gotoxy(x,y);
	fputs(str,stdout);
}