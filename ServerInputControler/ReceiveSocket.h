#pragma once
#include "afxsock.h"

#include "MouseControler.h"
#include "KeyboardControler.h"
#include "Log.h"
#include "Utils.h"

class CReceiveSocket :
	public CAsyncSocket
{
public:
	CReceiveSocket(void);
	~CReceiveSocket(void);

protected:
	void OnReceive(int nErrorCode);
	void OnSend(int nErrorCode);
	void OnOutOfBandData(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);

public:
	BOOL m_bConnected;
	UINT m_nLength;
	char m_szBuffer[4096];

	MouseControler mMouseControler;
	KeyboardControler mKeyboardControler;
};
