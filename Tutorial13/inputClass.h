/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:43
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\inputClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	inputClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef inputClass_h__
#define inputClass_h__

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass& other);
	~InputClass();

	bool initialize(HINSTANCE aHinstance, HWND aHwnd,
		int aWidth, int aHeight);
	void shutdown();
	bool frame();

	bool isEscapePressed();
	void getMouseLocation(int &posX, int &posY);

private:
	bool readKeyBoard();
	bool readMouse();
	void ProcessInput();

private:
	IDirectInput8 *m_directInput;
	IDirectInputDevice8 *m_keyBoard;
	IDirectInputDevice8 *m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif // inputClass_h__