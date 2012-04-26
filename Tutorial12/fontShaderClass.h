/********************************************************************
	created:	2012/04/25
	created:	25:4:2012   20:18
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\fontShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	fontShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef fontShaderClass_h__
#define fontShaderClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

class FontShaderClass
{
private:
	struct ConstantBufferType 
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct  PixelBufferType
	{
		D3DXVECTOR4 pixelColor;
	};

public:
	FontShaderClass();
	FontShaderClass(const FontShaderClass &aFontShaderClass);
	~FontShaderClass();

	bool initialize(
		ID3D11Device *aD3DDevice, HWND aHwnd);
	void shutdown();
	bool render(
		ID3D11DeviceContext *aD3DDevice, 
		int aIndexCount, D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView *aTexture, D3DXVECTOR4 aPixelColor);

private:
	bool initializeShader(
		ID3D11Device *aD3DDevice, HWND aHwnd,
		WCHAR *aVSFileName, WCHAR *aPSFileName);
	void shutdownShader();
	void outputShaderErrorMessage(
		ID3D10Blob *aErrorMessage, HWND aHwnd,
		WCHAR *aShaderFileName);

	bool setShaderParameters(
		ID3D11DeviceContext *aD3DDeviceContext, 
		D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix,
		D3DXMATRIX aProjectionMatrix, 
		ID3D11ShaderResourceView *aTexture,
		D3DXVECTOR4 aPixelColor);
	void renderShader(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_constantBuffer;
	ID3D11SamplerState *m_sampleState;

	ID3D11Buffer *m_pixelBuffer;
};

#endif // fontShaderClass_h__