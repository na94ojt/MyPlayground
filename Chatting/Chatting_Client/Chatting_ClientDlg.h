
// Chatting_ClientDlg.h : ��� ����
//

#pragma once


// CChatting_ClientDlg ��ȭ ����
class CChatting_ClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatting_ClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATTING_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_PortEdit;
	CEdit m_IdEdit;
	CIPAddressCtrl m_IpCtrl;
	afx_msg void OnBnClickedConnectButton();
};
