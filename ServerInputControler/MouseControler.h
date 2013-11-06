#pragma once
#include <windows.h>

#include "Utils.h"

#define GO_LEFT	'l'
#define GO_RIGHT 'r'
#define GO_UP 'u'
#define GO_DOWN	'd'

#define DO_SINGLE_CLICK	's'
#define DO_RIGHT_CLICK 'm'
#define DO_DOUBLE_CLICK	't'
#define DO_SCROLL 'o'

class MouseControler
{
private:
	INPUT mMove;
	INPUT mSingleClick[2];
	INPUT mDoublicClick[4];
	INPUT mRightClick[2];

public:
	MouseControler(void);
	~MouseControler(void);

	void Move(int dx, int dy);
	
	void Click();
	void DoubleClick();
	void RightClick();
	void Roll();
	void HandleMouseEvent(char* action, int size);

	/*void SendKey(short key);*/

	static void SetStep(int step=5);

private:
	static int sStep;
};
