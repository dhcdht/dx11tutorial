/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:28
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\systemclass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	systemclass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef systemClass_h__
#define systemClass_h__

//去除一部分windows.h中的代码，提高编译速度
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "inputclass.h"
#include "graphicsclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool initialize();
	void shutdown();
	void run();

	LRESULT CALLBACK messageHandler(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);

private:
	bool frame();
	void initializeWindows(int &aWidth, int &aHeight);
	void shutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass *m_input;
	GraphicsClass *m_graphics;
};

static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static SystemClass *applicationHandle = NULL;

#endif // systemClass_h__