/********************************************************************
	created:	2012/04/28
	created:	28:4:2012   10:11
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial15\cpuClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial15
	file base:	cpuClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef cpuClass_h__
#define cpuClass_h__

#pragma comment(lib, "pdh.lib")

#include <Pdh.h>

class CPUClass
{
public:
	CPUClass();
	CPUClass(const CPUClass &other);
	~CPUClass();

	void initialize();
	void shutdown();
	void frame();
	int getCPUPercentage();

private:
	bool m_canReadCPU;
	HQUERY m_queryHandler;
	HCOUNTER m_counterHandler;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};

#endif // cpuClass_h__