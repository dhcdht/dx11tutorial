/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   13:16
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial3\d3dClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial3
	file base:	d3dClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef d3dClass_h__
#define d3dClass_h__

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <D3Dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool initialize(int aWidth, int aHeight, bool vsync,
		HWND aHwnd, bool fullscreen, 
		float aScreenDepth, float aScreenNear);
	void shutdown();

	void beginScene(
		float aRed, float aGreen, float aBlue, float aAlpha);
	void endScene();

	ID3D11Device *getDevice();
	ID3D11DeviceContext *getDeviceContext();

	void getProjectionMatrix(D3DXMATRIX &projectionMatrix);
	void getWorldMatrix(D3DXMATRIX &worldMatrix);
	void getOrthoMatrix(D3DXMATRIX &orthoMatrix);

	void getVideoCardInfo(char* cardName, int &memory);

	void turnZBufferOn();
	void turnZBufferOff();

	void turnAlphaBlendingOn();
	void turnAlphaBlendingOff();

private:
	bool m_vsyncEnabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain *m_swapChain;
	ID3D11Device *m_device;
	ID3D11DeviceContext *m_deviceContext;
	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilState *m_depthStencilState;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RasterizerState *m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;

	ID3D11DepthStencilState *m_depthDisabledStencilState;

	ID3D11BlendState *m_alphaEnableBlendingState;
	ID3D11BlendState *m_alphaDisableBlendingState;
};

#endif // d3dClass_h__