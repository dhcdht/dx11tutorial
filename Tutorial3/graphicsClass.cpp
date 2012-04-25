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
	m_d3d = NULL;
}

GraphicsClass::GraphicsClass( const GraphicsClass& )
{

}

GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::initialize( int aWidth, int aHeight, HWND aHwnd )
{
	bool result;

	m_d3d = new D3DClass;
	if (NULL == m_d3d)
	{
		return false;
	}

	result = m_d3d->initialize(aWidth, aHeight, VSYNC_ENABLED,
		aHwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (NULL == result)
	{
		MessageBox(aHwnd, L"³õÊ¼»¯Direct3DÊ§°Ü£¡", L"´íÎó", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::shutdown()
{
	if (NULL != m_d3d)
	{
		m_d3d->shutdown();
		delete m_d3d;
		m_d3d = NULL;
	}

	return ;
}

bool GraphicsClass::frame()
{
	bool result;

	result = render();
	
	return result;
}

bool GraphicsClass::render()
{
	m_d3d->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

	m_d3d->endScene();

	return true;
}
