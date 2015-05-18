#include "stdafx.h"
#include "mylib.h"
#include "main.h"

#include <time.h>
#include <stdio.h>

#define MY_X 5
#define MY_Y 5

#define MY_B MY_X*MY_Y

#define MY_W 100
#define MY_H 100

int g_data[MY_Y][MY_X];

bool CheckGameOver()
{
	int a = 1;

	for (int y = 0; y<MY_Y; y++)
	{
		for (int x = 0; x<MY_X; x++)
		{
			if (a != g_data[y][x])
			{
				return false;
			}
			a++;
		}
	}
	return true;
}

bool Check(int sx,int sy,int dx,int dy)
{
	if (sx < 0 || sy < 0 || dx < 0 || dy < 0)
	{
		return false;
	}

	if (MY_X <= sx || MY_Y <= sy || MY_X <= dx || MY_Y <= dy)
	{
		return false;
	}

	if (MY_B == g_data[dy][dx])
	{
		g_data[dy][dx] = g_data[sy][sx];
		g_data[sy][sx] = MY_B;
		return true;
	}
	
	return false;
}

void MyIni(int count)
{
	int dx = MY_X-1;
	int dy = MY_Y-1;

	srand(time(NULL));

	for (int i = 0; i<count; i++)
	{
		int dir = rand()%4;

		if (0 == dir)
		{
			if (true == Check(dx-1,dy,dx,dy))
			{
				dx--;
			}
		}
		else if(1 == dir)
		{
			if (true == Check(dx+1,dy,dx,dy))
			{
				dx++;
			}
		}
		else if(2 == dir)
		{
			if (true == Check(dx,dy-1,dx,dy))
			{
				dy--;
			}
		}
		else if(3 == dir)
		{
			if (true == Check(dx,dy+1,dx,dy))
			{
				dy++;
			}
		}
	}
}

void OnCreate(HWND hWnd)
{
	int a = 1;

	for (int y = 0; y<MY_Y; y++)
	{
		for (int x = 0; x<MY_X; x++)
		{
			g_data[y][x] = a;
			a++;
		}
	}

	MyIni(100);
	
}
void OnPaint(HWND hWnd,HDC hdc)
{
	for (int y = 0; y<MY_Y; y++)
	{
		for (int x = 0; x<MY_X; x++)
		{
			int xpos = x*MY_W;
			int ypos = y*MY_H;

			Rectangle(hdc,xpos,ypos,xpos+MY_W,ypos+MY_H);

			if (MY_B != g_data[y][x])
			{
				char temp[80];
				sprintf(temp,"%d",g_data[y][x]);
				TextOut(hdc,xpos+MY_W/2,ypos+MY_H/2,temp,strlen(temp));
			}
		}
	}
}
void OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	int xpos = LOWORD(lParam);
	int ypos = HIWORD(lParam);

	int sx = xpos / MY_W;
	int sy = ypos / MY_H;

	if (true == Check(sx,sy,sx-1,sy))
	{
		InvalidateRect(hWnd,NULL,TRUE);
	}
	else if(true == Check(sx,sy,sx+1,sy))
	{
		InvalidateRect(hWnd,NULL,TRUE);
	}
	else if(true == Check(sx,sy,sx,sy-1))
	{
		InvalidateRect(hWnd,NULL,TRUE);
	}
	else if(true == Check(sx,sy,sx,sy+1))
	{
		InvalidateRect(hWnd,NULL,TRUE);
	}

	if (true == CheckGameOver())
	{
		MessageBox(hWnd,"Game Over","¾Ë¸²",MB_OK);
	}
}

void OnTimer(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	

}