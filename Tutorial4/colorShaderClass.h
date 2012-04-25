/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   20:10
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\colorShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	colorShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef colorShaderClass_h__
#define colorShaderClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>

using namespace std;

class ColorShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass &aColorShaderClass);
	~ColorShaderClass();

	bool initialize(ID3D11Device *aD3DDevice, HWND aHwnd);
	void shutdown();
	bool render(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount, D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix);

private:
	bool initializeShader(
		ID3D11Device *aD3DDevice, HWND aHwnd,
		WCHAR *aVSFileName, WCHAR *aPSFileName);
	void shutdownShader();
	void outputShaderErrorMessage(
		ID3D10Blob *aError, HWND aHwnd, WCHAR *aFileName);

	bool setShaderParameters(
		ID3D11DeviceContext *aD3DDeviceContext, 
		D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix,
		D3DXMATRIX aProjectionMatrix);
	void renderShader(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
};

#endif // colorShaderClass_h__