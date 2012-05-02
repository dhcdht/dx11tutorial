/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:26
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\timerClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	timerClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "timerClass.h"

TimerClass::TimerClass()
{

}

TimerClass::TimerClass( const TimerClass &other )
{

}

TimerClass::~TimerClass()
{

}

bool TimerClass::initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (0 == m_frequency)
	{
		return false;
	}

	m_ticksPerMs = (float)(m_frequency / 1000);
	
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void TimerClass::frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return ;
}

float TimerClass::getTime()
{
	return m_frameTime;
}
