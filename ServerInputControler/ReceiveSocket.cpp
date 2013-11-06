#include "StdAfx.h"
#include "ReceiveSocket.h"

CReceiveSocket::CReceiveSocket(void)
{
}

CReceiveSocket::~CReceiveSocket(void)
{
}

void CReceiveSocket::OnSend(int nErrorCode){}

void CReceiveSocket::OnOutOfBandData(int nErrorCode){}

void CReceiveSocket::OnAccept(int nErrorCode){}

void CReceiveSocket::OnConnect(int nErrorCode){}

void CReceiveSocket::OnClose(int nErrorCode){}


//Handle message from client.
//There there types of message:
//1.mouse action, it's like "r", "u" etc.
//2.set move step, it's like "#10","#20".
//3.text, it's like "##abcdefg","##hello".
//4.mouse moving, it's like "###r20u52", "###l2d100"
void CReceiveSocket::OnReceive(int nErrorCode)
{
	m_nLength = Receive(m_szBuffer,sizeof(m_szBuffer),0);

	Log::I(L"ReceiveSocket", Utils::getWChar(m_szBuffer), m_nLength);
	
	if(m_nLength < 1) return;

	if(m_nLength>3 && m_szBuffer[0]=='#' && m_szBuffer[1]=='#' && m_szBuffer[2]=='#')//mouse moving, it's like "###r20u52", "###l2d100"
	{
		mMouseControler.HandleMouseEvent(m_szBuffer, m_nLength);
	}
	else if(m_nLength>2 && m_szBuffer[0]=='#' && m_szBuffer[1]=='#')// text message like "##aa", "##bb"
	{
		mKeyboardControler.SendMultiKey(m_szBuffer+2, m_nLength - 2);
	}
	else if(m_nLength>1 && m_szBuffer[0]=='#')//set move step like "#10","#20"
	{
		MouseControler::SetStep(atoi(m_szBuffer + 1));
	}
	else//mouse action: move or click, like "rr","rrddllrr"
	{
		mMouseControler.HandleMouseEvent(m_szBuffer, m_nLength);
	}
}