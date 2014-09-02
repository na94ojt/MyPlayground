
// Chatting_ClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Chatting_Client.h"
#include "Chatting_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatting_ClientDlg ��ȭ ����


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


// CChatting_ClientDlg �޽��� ó����

BOOL CChatting_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChatting_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CChatting_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatting_ClientDlg::OnBnClickedConnectButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
