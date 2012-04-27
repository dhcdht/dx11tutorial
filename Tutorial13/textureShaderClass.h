/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   22:46
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial5\textureShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial5
	file base:	textureShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef textureShaderClass_h__
#define textureShaderClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>

using namespace std;

class TextureShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	TextureShaderClass();
	TextureShaderClass(const TextureShaderClass&);
	~TextureShaderClass();

	bool initialize(ID3D11Device*, HWND);
	void shutdown();
	bool render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);

private:
	bool initializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void shutdownShader();
	void outputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool setShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	void renderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;

	ID3D11SamplerState* m_sampleState;
};

#endif // textureShaderClass_h__