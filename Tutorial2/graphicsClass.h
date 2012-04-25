/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:47
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\graphicsClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	graphicsClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef graphicsClass_h__
#define graphicsClass_h__

#include <Windows.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool initialize(int aWidth, int aHeight, HWND aHwnd);
	void shutdown();
	bool frame();

private:
	bool render();
};

#endif // graphicsClass_h__