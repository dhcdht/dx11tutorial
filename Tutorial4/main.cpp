/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   13:12
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\main.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	main
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "systemClass.h"

int WINAPI WinMain( 
	__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in LPSTR lpCmdLine, __in int nShowCmd )
{
	SystemClass *system;
	bool result;

	system = new SystemClass;
	if (NULL == system)
	{
		return 0;
	}

	result = system->initialize();
	if (result)
	{
		system->run();
	}

	system->shutdown();
	delete system;
	system = NULL;

	return 0;
}