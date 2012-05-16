/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:06
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\fpsClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	fpsClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef fpsClass_h__
#define fpsClass_h__

#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <MMSystem.h>

class FPSClass
{
public:
	FPSClass();
	FPSClass(const FPSClass &other);
	~FPSClass();

	void initialize();
	void frame();
	int getFPS();

private:
	int m_fps;
	int m_count;
	unsigned long m_startTime;
};

#endif // fpsClass_h__