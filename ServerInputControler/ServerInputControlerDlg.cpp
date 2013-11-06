// ServerInputControlerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerInputControler.h"
#include "ServerInputControlerDlg.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CServerInputControlerDlg 对话框


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


// CServerInputControlerDlg 消息处理程序

BOOL CServerInputControlerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	char name[80];
	CString IP;
	hostent* pHost; 
	gethostname(name, 128);//获得主机名 
	pHost = gethostbyname(name);//获得主机结构 
	IP = inet_ntoa(*(in_addr *)pHost->h_addr);
	m_IP.ReplaceSel(IP);

	m_Port.ReplaceSel(_T("9999"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerInputControlerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerInputControlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerInputControlerDlg::OnBnClickedListen()
{
	// TODO: 在此添加控件通知处理程序代码
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
	////“侦听”成功，等待连接请求
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
