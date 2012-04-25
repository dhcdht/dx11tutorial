/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   19:52
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\modelClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	modelClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef modelClass_h__
#define modelClass_h__

#include <d3d11.h>
#include <D3DX10math.h>

#include "textureClass.h"

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	ModelClass();
	ModelClass(const ModelClass &aModelClass);
	~ModelClass();

	bool initialize(ID3D11Device *aD3DDevice, WCHAR *aFileName);
	void shutdown();
	void render(ID3D11DeviceContext *aD3DDeviceContext);

	int getIndexCount();

	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device *aD3DDevice);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext *aD3DDeviceContext);

	bool loadTexture(ID3D11Device *aD3DDevice, WCHAR *aFileName);
	void releaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;

	TextureClass *m_texture;
};

#endif // modelClass_h__