/********************************************************************
	created:	2012/05/02
	created:	2:5:2012   20:40
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial17\multiTextureShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial17
	file base:	multiTextureShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef multiTextureShaderClass_h__
#define multiTextureShaderClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

class MultiTextureShaderClass
{
private:
	struct MatrixBufferType 
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	MultiTextureShaderClass();
	MultiTextureShaderClass(const MultiTextureShaderClass &other);
	~MultiTextureShaderClass();

	bool initialize(ID3D11Device *aD3DDevice, HWND aHwnd);
	void shutdown();
	bool render(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount,
		D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix,
		D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView **aTextures);

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
		D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView **aTextures);
	void renderShader(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11SamplerState *m_sampleState;
};

#endif // multiTextureShaderClass_h__