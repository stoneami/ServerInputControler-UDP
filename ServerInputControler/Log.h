#pragma once

class Log
{
public:
	Log(void);
	~Log(void);

	static void W(wchar_t* tag, wchar_t* msg, int msgLen);
	static void E(wchar_t* tag, wchar_t* msg, int msgLen);
	static void I(wchar_t* tag, wchar_t* msg, int msgLen);

	static void W(wchar_t* tag, wchar_t* msg);
	static void E(wchar_t* tag, wchar_t* msg);
	static void I(wchar_t* tag, wchar_t* msg);
private:
	static void PrintLog(char type, wchar_t* tag, wchar_t* buf, int bufLen);

	static const int MAX_CHAR=200;
};
