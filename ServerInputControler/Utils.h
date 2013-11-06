#pragma once

class Utils
{
public:
	Utils(void);
	~Utils(void);

	static wchar_t* getWChar(char * str);
	static wchar_t* getWChar(int i);
	static wchar_t* getWChar(char* text, int len);
	
	static void PrintByte(char c);
	static void PrintShort(short s);
};
