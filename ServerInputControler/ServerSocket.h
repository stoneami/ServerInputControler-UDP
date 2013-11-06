#pragma once
#include "afxsock.h"
#include "ReceiveSocket.h"

class ServerSocket :
	public CAsyncSocket
{
public:
	ServerSocket(void);
	~ServerSocket(void);

protected:
	void OnReceive(int nErrorCode);
	//void OnSend(int nErrorCode);
	//void OnOutOfBandData(int nErrorCode);
	//void OnAccept(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);

public:
	CReceiveSocket* m_pSocket;

private:
	TCHAR m_szBuffer[4096];
};
