// ServerInputControler.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CServerInputControlerApp:
// �йش����ʵ�֣������ ServerInputControler.cpp
//

class CServerInputControlerApp : public CWinApp
{
public:
	CServerInputControlerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServerInputControlerApp theApp;