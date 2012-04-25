/********************************************************************
	created:	2012/03/25
	created:	25:3:2012   10:11
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial6\lightShaderClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial6
	file base:	lightShaderClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef lightShaderClass_h__
#define lightShaderClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>

using namespace std;

class LightShaderClass
{
private:
	struct MatrixBufferType 
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct CameraBufferType 
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct LightBufferType 
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass &aLightShaderClass);
	~LightShaderClass();

	bool initialize(ID3D11Device *aD3DDevice, HWND aHwnd);
	void shutdown();
	bool render(ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount, D3DXMATRIX aWorldMatrix,
		D3DXMATRIX aViewMatrix,
		D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView *aShaderResourceView,
		D3DXVECTOR3 aLightDirection,
		D3DXVECTOR4 aAmbientColor,
		D3DXVECTOR4 aDiffuseColor,
		D3DXVECTOR3 aCameraPosition, 
		D3DXVECTOR4 aSpecularColor, 
		float aSpecularPower);

private:
	bool initializeShader(ID3D11Device *aD3DDevice,
		HWND aHwnd, WCHAR *aVSFileName,
		WCHAR *aPSFileName);
	void shutdownShader();
	void outputShaderErrorMessage(ID3D10Blob *aError,
		HWND aHwnd, WCHAR *aFileName);

	bool setShaderParameters(
		ID3D11DeviceContext *aD3DDeviceContext,
		D3DXMATRIX aWorldMatrix, 
		D3DXMATRIX aViewMatrix,
		D3DXMATRIX aProjectionMatrix,
		ID3D11ShaderResourceView *aShaderResourceView,
		D3DXVECTOR3 aLightDirection,
		D3DXVECTOR4 aAmbientColor,
		D3DXVECTOR4 aDiffuseColor,
		D3DXVECTOR3 aCameraPosition,
		D3DXVECTOR4 aSpecularColor,
		float aSpecularPower);
	void renderShader(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aIndexCount);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_matrixBuffer;

	ID3D11Buffer *m_cameraBuffer;
	ID3D11Buffer *m_lightBuffer;
};

#endif // lightShaderClass_h__