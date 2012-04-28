/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:47
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\graphicsClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	graphicsClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef graphicsClass_h__
#define graphicsClass_h__

#include "d3dClass.h"
#include "cameraClass.h"
#include "modelClass.h"
#include "lightShaderClass.h"
#include "lightClass.h"
#include "textureShaderClass.h"
#include "bitmapClass.h"
#include "textClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool initialize(int aWidth, int aHeight, HWND aHwnd);
	void shutdown();
	bool frame(int aMouseX, int aMouseY,
		int aFPS, int aCPU, float aFrameTime);

private:
	bool render(float aRotation);

	D3DClass *m_d3d;
	CameraClass *m_camera;
	ModelClass *m_model;
	
	LightShaderClass *m_lightShader;
	LightClass *m_light;

	TextureShaderClass *m_textureShader;
	BitmapClass *m_bitmap;

	TextClass *m_text;
};

#endif // graphicsClass_h__