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

	m_lightShader = NULL;
	m_light = NULL;

	m_textureShader = 0;
	m_bitmap = 0;

	m_text = 0;
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
	//m_camera->setPosition(0.0f, 0.0f, -10.0f);

	m_model = new ModelClass;
	if (NULL == m_model)
	{
		return false;
	}
	
	result = m_model->initialize(m_d3d->getDevice(), "./obj/cube.txt", L"./tex/box.png");
	if (!result)
	{
		MessageBox(aHwnd, L"无法初始化模型", L"错误", MB_OK);
		return false;
	}

	m_lightShader = new LightShaderClass;
	if (NULL == m_lightShader)
	{
		return false;
	}

	result = m_lightShader->initialize(
		m_d3d->getDevice(), aHwnd);
	if (!result)
	{
		MessageBox(aHwnd, L"不能加载着色器", L"错误", MB_OK);
		return false;
	}

	m_light = new LightClass;
	if (NULL == m_light)
	{
		return false;
	}

	m_light->setAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setDirection(0.0f, 0.0f, 1.0f);
	m_light->setSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setSpecularPower(50.0f);
	
	m_textureShader = new TextureShaderClass;
	if (NULL == m_textureShader)
	{
		return false;
	}

	result = m_textureShader->initialize(
		m_d3d->getDevice(), aHwnd);
	if (!result)
	{
		MessageBox(aHwnd, L"不能加载着色器", L"错误", MB_OK);
		return false;
	}

	m_bitmap = new BitmapClass;
	if (!m_bitmap)
	{
		return false;
	}

	result = m_bitmap->initialize(
		m_d3d->getDevice(), aWidth, aHeight, 
		L"./tex/sky.dds", 50, 50);
	if (!result)
	{
		MessageBox(aHwnd, L"不能初始化位图资源", L"错误", MB_OK);
		return false;
	}

	D3DXMATRIX baseViewMatrix;
	m_camera->setPosition(0.0f, 0.0f, -1.0f);
	m_camera->render();
	m_camera->getViewMatrix(baseViewMatrix);

	m_text = new TextClass;
	if (!m_text)
	{
		return false;
	}

	result = m_text->initialize(
		m_d3d->getDevice(), m_d3d->getDeviceContext(),
		aHwnd, aWidth, aHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(aHwnd, L"初始化字体对象失败", L"Error", MB_OK);
		return false;
	}


	m_camera->setPosition(0.0f, 0.0f, -10.0f);
	return true;
}

void GraphicsClass::shutdown()
{
	if (m_text)
	{
		delete m_text;
		m_text = 0;
	}

	if (m_bitmap)
	{
		m_bitmap->shutdown();
		m_bitmap = 0;
	}

	if (m_textureShader)
	{
		m_textureShader->shutdown();
		delete m_textureShader;
		m_textureShader = 0;
	}

	if (NULL != m_light)
	{
		delete m_light;
		m_light = NULL;
	}

	if (NULL != m_lightShader)
	{
		m_lightShader->shutdown();
		delete m_lightShader;
		m_lightShader = NULL;
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

	static float rotation = 0.0f;

	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	result = render(rotation);
	
	return result;
}

bool GraphicsClass::render(float aRotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	D3DXMATRIX orthoMatrix;

	m_d3d->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

	m_camera->render();
	
	m_camera->getViewMatrix(viewMatrix);
	m_d3d->getWorldMatrix(worldMatrix);
	m_d3d->getProjectionMatrix(projectionMatrix);

	m_d3d->getOrthoMatrix(orthoMatrix);
	
	m_d3d->turnZBufferOff();

	result = m_bitmap->render(
		m_d3d->getDeviceContext(), 50, 50);
	if (!result)
	{
		return false;
	}

	result = m_textureShader->render(
		m_d3d->getDeviceContext(), m_bitmap->getIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix,
		m_bitmap->getTexture());
	if (!result)
	{
		return false;
	}

	m_d3d->turnZBufferOn();
	
	D3DXMatrixRotationY(&worldMatrix, aRotation);
	
	m_model->render(m_d3d->getDeviceContext());

	result = m_lightShader->render(
		m_d3d->getDeviceContext(), m_model->getIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_model->getTexture(),
		m_light->getDirection(),
		m_light->getAmbientColor(),
		m_light->getDiffuseColor(),
		m_camera->getPosition(),
		m_light->getSpecularColor(),
		m_light->getSpecularPower());
	if (!result)
	{
		return false;
	}
	
	m_d3d->turnZBufferOff();
	m_d3d->turnAlphaBlendingOn();

	result = m_text->render(
		m_d3d->getDeviceContext(),
		worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_d3d->turnAlphaBlendingOff();
	m_d3d->turnZBufferOn();

	m_d3d->endScene();

	return true;
}
