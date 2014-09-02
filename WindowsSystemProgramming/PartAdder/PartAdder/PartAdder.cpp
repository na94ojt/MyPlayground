// PartAdder.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <tchar.h>
#include <string.h>
#include <Windows.h>

typedef struct
{
	HANDLE hProcess;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int result;
	TCHAR command[20];
}ADDER;


int _tmain(int argc, _TCHAR* argv[])
{
	ADDER OneToFive,SixToTen;
	STARTUPINFO si_example;

	_tcscpy(OneToFive.command,_T("OneToFive.exe\0"));
	_tcscpy(SixToTen.command,_T("SixToTen.exe\0"));

	si_example.cb = sizeof(si_example);
	si_example.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si_example.dwX = 100;
	si_example.dwY = 200;
	si_example.lpTitle = _T("I am a boy!");

	CreateProcess(NULL, OneToFive.command, NULL, NULL, TRUE,

	return 0;
}

