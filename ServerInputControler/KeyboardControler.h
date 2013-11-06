#pragma once

#define MAX_KEYS 100

class KeyboardControler
{
private:
	INPUT mKeyboard[2];
	short mKeyUnicode[MAX_KEYS];

public:
	KeyboardControler(void);
	~KeyboardControler(void);

	void SendKey(short key);
	void SendMultiKey(char *keys, int size);

	int GetKeyCount(const char* utf8, int size);
	short* GetKeyUnicodes(const char* utf8, int size);
};
