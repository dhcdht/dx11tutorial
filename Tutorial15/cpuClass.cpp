/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:15
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\cpuClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	cpuClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "cpuClass.h"

CPUClass::CPUClass()
{

}

CPUClass::CPUClass( const CPUClass &other )
{

}

CPUClass::~CPUClass()
{

}

void CPUClass::initialize()
{
	PDH_STATUS status;

	m_canReadCPU = true;

	status = PdhOpenQuery(NULL, 0, &m_queryHandler);
	if (ERROR_SUCCESS != status)
	{
		m_canReadCPU = false;
	}

	status = PdhAddCounter(m_queryHandler,
		TEXT("\\Processor(_Total)\\% processor time"), 0,
		&m_counterHandler);
	if (ERROR_SUCCESS != status)
	{
		m_canReadCPU = false;
	}

	m_lastSampleTime = GetTickCount();

	m_cpuUsage = 0;

	return ;
}

void CPUClass::shutdown()
{
	if (m_canReadCPU)
	{
		PdhCloseQuery(m_queryHandler);
	}

	return ;
}

int CPUClass::getCPUPercentage()
{
	int usage;

	if (m_canReadCPU)
	{
		usage = (int)m_cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}

void CPUClass::frame()
{
	PDH_FMT_COUNTERVALUE value;

	if (m_canReadCPU)
	{
		if ((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount();

			PdhCollectQueryData(m_queryHandler);

			PdhGetFormattedCounterValue(
				m_counterHandler, PDH_FMT_LONG, NULL, &value);

			m_cpuUsage = value.longValue;
		}
	}

	return ;
}
