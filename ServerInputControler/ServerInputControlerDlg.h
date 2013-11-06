// ServerInputControlerDlg.h : ͷ�ļ�
//

#pragma once
#include "ServerSocket.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "Log.h"

// CServerInputControlerDlg �Ի���
class CServerInputControlerDlg : public CDialog
{
// ����
public:
	CServerInputControlerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVERINPUTCONTROLER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedListen();
	BOOL DestroyWindow();
	ServerSocket m_serverSocket;
	CNetAddressCtrl m_IP;
	CEdit m_Port;

	char m_szBuffer[4096];
};
