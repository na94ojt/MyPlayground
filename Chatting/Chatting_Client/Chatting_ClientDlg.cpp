
// Chatting_ClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Chatting_Client.h"
#include "Chatting_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatting_ClientDlg 대화 상자


CChatting_ClientDlg::CChatting_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatting_ClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatting_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PORT_EDIT, this->m_PortEdit);
	DDX_Control(pDX, IDC_ID_EDIT, this->m_IdEdit);
	DDX_Control(pDX, IDC_SERVER_IPADDRESS, this->m_IpCtrl);
}

BEGIN_MESSAGE_MAP(CChatting_ClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CChatting_ClientDlg::OnBnClickedConnectButton)
END_MESSAGE_MAP()


// CChatting_ClientDlg 메시지 처리기

BOOL CChatting_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatting_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatting_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatting_ClientDlg::OnBnClickedConnectButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!this->m_IpCtrl.IsBlank() && 0 < this->m_IdEdit.GetWindowTextLengthW() && 0 < this->m_PortEdit.GetWindowTextLengthW())
	{
		CString strIpAddress;
		DWORD dwIp;
		BYTE a, b, c, d;

		m_IpCtrl.GetAddress(dwIp);
		
		a = HIBYTE(HIWORD(dwIp));
		b = LOBYTE(HIWORD(dwIp));
		c = HIBYTE(LOWORD(dwIp));
		d = LOBYTE(LOWORD(dwIp));

		strIpAddress.Format(_T("%d.%d.%d.%d"), a, b, c, d);

		TCHAR TIpAddress[30];
		TCHAR TPort[10];
		CString strPort;
		char IpAddress[30];

		_tcscpy(TIpAddress, strIpAddress);
		WideCharToMultiByte(CP_ACP, 0, TIpAddress, 30, IpAddress, 30, NULL, NULL);
		
		this->m_PortEdit.GetWindowTextW(strPort);
		_tcscpy(TPort, strPort);

		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN sock_addr;
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_addr.s_addr = inet_addr(IpAddress);
		sock_addr.sin_port = htons(_tstoi(TPort));
		
		if (-1 == connect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)))
		{
			MessageBox(L"Connect Error", L"Can't Connect To Server", MB_OK);
		}

		CDialog::OnOK();
	}
	else
	{
		MessageBox(L"Fill the Blank", L"Fill the Blank", MB_OK);
	}
	/*
	g_sock_addr.sin_family = AF_INET;
	g_sock_addr.sin_addr.s_addr = inet_addr(this->m_IpCtrl.)
	*/
}
