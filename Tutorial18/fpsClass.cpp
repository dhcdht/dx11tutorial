/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:09
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\fpsClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	fpsClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "fpsClass.h"

FPSClass::FPSClass()
{

}

FPSClass::FPSClass( const FPSClass &other )
{

}

FPSClass::~FPSClass()
{

}

void FPSClass::initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();

	return ;
}

void FPSClass::frame()
{
	m_count++;

	if (timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_startTime = timeGetTime();
	}
}

int FPSClass::getFPS()
{
	return m_fps;
}
