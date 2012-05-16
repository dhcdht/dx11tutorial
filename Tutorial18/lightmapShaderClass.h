/********************************************************************
	created:	2012/05/14
	created:	14:5:2012   21:08
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial18\lightmapShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial18
	file base:	lightmapShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef lightmapShaderClass_h__
#define lightmapShaderClass_h__

#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

class LightmapShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	LightmapShaderClass();
	LightmapShaderClass(const LightmapShaderClass &other);
	~LightmapShaderClass();

	bool initialize(ID3D11Device *aD3DDevice, HWND aHwnd);
	void shutdown();
	bool render(ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount, D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView **aTextures);

private:
	bool initializeShader(ID3D11Device *aD3DDevice,
		HWND aHwnd)
};

#endif // lightmapShaderClass_h__