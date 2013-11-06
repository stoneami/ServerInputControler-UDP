#include "StdAfx.h"
#include "KeyboardControler.h"
#include "Utils.h"

KeyboardControler::KeyboardControler(void)
{
}

KeyboardControler::~KeyboardControler(void)
{
}

//key is an unicode defined key value
void KeyboardControler::SendKey(short key)
{
	ZeroMemory(mKeyboard, sizeof(INPUT));
	mKeyboard[0].type = INPUT_KEYBOARD;
	mKeyboard[1].type = INPUT_KEYBOARD;
	mKeyboard[0].ki.wVk=mKeyboard[1].ki.wVk=0;
	mKeyboard[0].ki.wScan=mKeyboard[1].ki.wScan=key;
	mKeyboard[0].ki.dwFlags=KEYEVENTF_UNICODE;
	mKeyboard[1].ki.dwFlags=KEYEVENTF_UNICODE|KEYEVENTF_KEYUP;
	SendInput(2, mKeyboard, sizeof(INPUT));
}

short* KeyboardControler::GetKeyUnicodes(const char* utf8, const int size)
{
	ZeroMemory(mKeyUnicode, sizeof(short));

	int cur=0;

	for(int i=0;i<size && cur<MAX_KEYS;cur++)
	{
		if((utf8[i] & 0x80) == 0)//one byte
		{
			mKeyUnicode[cur] = utf8[i];
			i++;
		}
		else if((utf8[i] & 0xe0) == 0xc0)//two bytes
		{
			short high = utf8[i]&0x1f;
			short low = utf8[i+1]&0x3f;
			mKeyUnicode[cur] = (high<<6)|low;
			i+=2;
		}
		else if((utf8[i] & 0xf0) == 0xe0)//three bytes
		{
			short high = utf8[i]&0x0f;
			short mid = utf8[i+1]&0x3f;
			short low = utf8[i+2]&0x3f;
			mKeyUnicode[cur] = (high<<12)|(mid<<6)|low;
			i+=3;
//mKeyUnicode[cur] = 0x4e2d;//บบ
		}
		else
		{
			mKeyUnicode[cur] = utf8[i++];
		}
	}

	return mKeyUnicode;
}

//keys is a utf-8 array
void KeyboardControler::SendMultiKey(char *utf8, int size)
{
	short* keys = GetKeyUnicodes(utf8, size);
	int count = GetKeyCount(utf8, size);

	for(int i=0;i<count;i++)
	{
		SendKey(keys[i]);
	}
}

int KeyboardControler::GetKeyCount(const char* utf8, int size)
{
	int count=0;
	for(int i=0;i<size;)
	{
		if((utf8[i] & 0x80) == 0)//one byte
		{
			i++;
		}
		else if((utf8[i] & 0xe0) == 0xc0)//two bytes
		{
			i+=2;
		}
		else if((utf8[i] & 0xf0) == 0xe0)//three bytes
		{
			i+=3;
		}
		else
		{
			i++;
		}

		count++;
	}
	return count;
}
