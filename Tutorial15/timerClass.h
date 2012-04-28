/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:23
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\timerClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	timerClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef timerClass_h__
#define timerClass_h__

#include <Windows.h>

class TimerClass
{
public:
	TimerClass();
	TimerClass(const TimerClass &other);
	~TimerClass();

	bool initialize();
	void frame();

	float getTime();

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};

#endif // timerClass_h__