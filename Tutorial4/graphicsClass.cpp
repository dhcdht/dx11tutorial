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
	m_camera = NULL;
	m_model = NULL;
	m_colorShader = NULL;
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
		MessageBox(aHwnd, L"初始化Direct3D失败！", L"错误", MB_OK);
		return false;
	}

	m_camera = new CameraClass;
	if (NULL == m_camera)
	{
		return false;
	}
	m_camera->setPosition(0.0f, 0.0f, -10.0f);

	m_model = new ModelClass;
	if (NULL == m_model)
	{
		return false;
	}
	
	result = m_model->initialize(m_d3d->getDevice());
	if (!result)
	{
		MessageBox(aHwnd, L"无法初始化模型", L"错误", MB_OK);
		return false;
	}

	m_colorShader = new ColorShaderClass;
	if (NULL == m_colorShader)
	{
		return false;
	}
	result = m_colorShader->initialize(m_d3d->getDevice(), aHwnd);
	if (!result)
	{
		MessageBox(aHwnd, L"不能加载着色器", L"错误", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::shutdown()
{
	if (NULL != m_colorShader)
	{
		m_colorShader->shutdown();
		delete m_colorShader;
		m_colorShader = NULL;
	}

	if (NULL != m_model)
	{
		m_model->shutdown();
		delete m_model;
		m_model = NULL;
	}

	if (NULL != m_camera)
	{
		delete m_camera;
		m_camera = NULL;
	}

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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	m_d3d->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

	m_camera->render();

	m_camera->getViewMatrix(viewMatrix);
	m_d3d->getWorldMatrix(worldMatrix);
	m_d3d->getProjectionMatrix(projectionMatrix);
	
	m_model->render(m_d3d->getDeviceContext());

	result = m_colorShader->render(
		m_d3d->getDeviceContext(), m_model->getIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	m_d3d->endScene();

	return true;
}
