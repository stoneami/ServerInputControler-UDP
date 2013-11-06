#include "StdAfx.h"
#include "ServerSocket.h"

ServerSocket::ServerSocket(void)
{
}

ServerSocket::~ServerSocket(void)
{
}

void ServerSocket::OnReceive(int nErrorCode)
{
	//TRACE1("OnReceive: Get a message... %d", nErrorCode);
	Log::I(L"ServerSocket", L"OnReceive()...");

	int nRead;
	CString strSendersIp;
	UINT uSendersPort;
	// Could use Receive here if you don't need the senders address & port
	nRead = ReceiveFromEx(m_szBuffer, 4096, strSendersIp, uSendersPort); 

	switch (nRead)
	{
	case 0: // Connection was closed.
		Log::I(L"ServerSocket", L"OnReceive(): NO data?");
		Close();      
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK) 
		{
			Log::E(L"ServerSocket", L"OnReceive(): SOCKET ERROR!");
			Close();
		}
		break;
	default: // Normal case: Receive() returned the # of bytes received.
		m_szBuffer[nRead] = 0; //terminate the string (assuming a string for this example) 
		Log::I(L"ServerSocket", m_szBuffer, nRead);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

//void ServerSocket::OnSend(int nErrorCode)
//{
//}

//void ServerSocket::OnAccept(int nErrorCode)
//{
//	//侦听到连接请求，调用Accept函数
//	CReceiveSocket* pSocket = new CReceiveSocket();
//	if(Accept(*pSocket))
//	{
//		pSocket->AsyncSelect(FD_READ);
//		m_pSocket=pSocket;
//	}
//	else
//		delete pSocket;
//}

void ServerSocket::OnConnect(int nErrorCode)
{
	TRACE1("OnConnect: Get a message... %d", nErrorCode);
}

void ServerSocket::OnClose(int nErrorCode)
{
}
