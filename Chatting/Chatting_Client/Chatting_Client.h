
// Chatting_Client.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChatting_ClientApp:
// �� Ŭ������ ������ ���ؼ��� Chatting_Client.cpp�� �����Ͻʽÿ�.
//

class CChatting_ClientApp : public CWinApp
{
public:
	CChatting_ClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CChatting_ClientApp theApp;