#include "StdAfx.h"
#include "Utils.h"

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}

wchar_t* Utils::getWChar(char* text)
{
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, text, -1, NULL, 0);
	wchar_t *pwText = new wchar_t[dwNum];
	MultiByteToWideChar (CP_ACP, 0, text, -1, pwText, dwNum);

	return pwText;
}

wchar_t* Utils::getWChar(char* text, int len)
{
	wchar_t *pwText = new wchar_t[len+1];
	pwText[len] = '\0';
	MultiByteToWideChar (CP_ACP, 0, text, -1, pwText, len);

	return pwText;
}

wchar_t* Utils::getWChar(int i)
{
	char text[10];
	itoa(i, text, 10);

	return getWChar(text);
}

void Utils::PrintByte(char c)
{
	wchar_t bits[9]={0};


	for(int i=0;i<8;i++)
	{
		if((c>>7)==0) bits[i]='0';
		else bits[i]='1';
		c<<=1;
	}
	AfxMessageBox(bits);
}

void Utils::PrintShort(short s)
{
	wchar_t bits[17]={0};

	for(int i=0;i<16;i++)
	{
		if((s>>15)==0) bits[i]='0';
		else bits[i]='1';
		s<<=1;
	}
	AfxMessageBox(bits);
}