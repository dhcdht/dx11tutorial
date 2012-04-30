/********************************************************************
	created:	2012/04/24
	created:	24:4:2012   19:18
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial11\bitmapClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial11
	file base:	bitmapClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef bitmapClass_h__
#define bitmapClass_h__

#include <d3d11.h>
#include <D3DX10math.h>

#include "textureClass.h"

class BitmapClass
{
private:
	struct VertexType 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass &aBitmapClass);
	~BitmapClass();

	bool initialize(ID3D11Device *aD3DDevice, 
		int aWidth, int aHeight, WCHAR *aTextureFileName,
		int aBitmapWidth, int aBitmapHeight);
	void shutdown();
	bool render(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aPositionX, int aPositionY);

	int getIndexCount();
	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device *aD3DDevice);
	void shutdownBuffers();
	bool updateBuffers(
		ID3D11DeviceContext *aD3DDeviceContext,
		int aPositionX,int aPositionY);
	void renderBuffers(ID3D11DeviceContext *aD3DDeviceContext);
	
	bool loadTexture(ID3D11Device *aD3DDevice,
		WCHAR *aTextureFileName);
	void releaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	TextureClass *m_texture;

	int m_screenWidth;
	int m_screenHeight;
	int m_bitmapWidth;
	int m_bitmapHeight;
	int m_previousPosX;
	int m_previousPosY;
};

#endif // bitmapClass_h__