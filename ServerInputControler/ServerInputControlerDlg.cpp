// ServerInputControlerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerInputControler.h"
#include "ServerInputControlerDlg.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CServerInputControlerDlg �Ի���


CServerInputControlerDlg::CServerInputControlerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CServerInputControlerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerInputControlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NETADDRESS, m_IP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_Port);
}

BEGIN_MESSAGE_MAP(CServerInputControlerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Listen, &CServerInputControlerDlg::OnBnClickedListen)
END_MESSAGE_MAP()


// CServerInputControlerDlg ��Ϣ�������

BOOL CServerInputControlerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	char name[80];
	CString IP;
	hostent* pHost; 
	gethostname(name, 128);//��������� 
	pHost = gethostbyname(name);//��������ṹ 
	IP = inet_ntoa(*(in_addr *)pHost->h_addr);
	m_IP.ReplaceSel(IP);

	m_Port.ReplaceSel(_T("9999"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerInputControlerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerInputControlerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerInputControlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerInputControlerDlg::OnBnClickedListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_serverSocket.m_hSocket==INVALID_SOCKET)
	{
		Log::I(L"ServerInputControlerDlg", L"creating socket...");
		BOOL bFlag=m_serverSocket.Create(9999, SOCK_DGRAM, FD_READ);
		if(! bFlag)
		{
			AfxMessageBox(_T("Socket Error"));
			m_serverSocket.Close();
			PostQuitMessage(0);
			return;
		}
	}

	//m_serverSocket.SetSockOpt(SO_SNDBUF, m_szBuffer, sizeof(m_szBuffer));
	//m_serverSocket.SetSockOpt(SO_RCVBUF, m_szBuffer, sizeof(m_szBuffer));

	////Log::I(L"ServerInputControlerDlg", L"start listenning...");
	////���������ɹ����ȴ���������
	//if(!(m_serverSocket.Listen(1)))
	//{
	//	int nErrorCode = m_serverSocket.GetLastError();
	//	TRACE1("......%d",nErrorCode);
	//	if(nErrorCode != WSAEWOULDBLOCK)
	//	{
	//		AfxMessageBox(_T("Socket Error!"));
	//		m_serverSocket.Close();
	//		PostQuitMessage(0);
	//		return;
	//	}
	//}
}

BOOL CServerInputControlerDlg::DestroyWindow()
{
	if(m_serverSocket != NULL && m_serverSocket.m_hSocket!=INVALID_SOCKET)
	{
		//m_serverSocket.Close();
	}
	return CDialog::DestroyWindow();
}
