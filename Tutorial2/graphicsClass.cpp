/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   13:10
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\graphicsClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	graphicsClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "graphicsClass.h"

GraphicsClass::GraphicsClass()
{

}

GraphicsClass::GraphicsClass( const GraphicsClass& )
{

}

GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::initialize( int aWidth, int aHeight, HWND aHwnd )
{
	return true;
}

void GraphicsClass::shutdown()
{
	return ;
}

bool GraphicsClass::frame()
{
	return true;
}
