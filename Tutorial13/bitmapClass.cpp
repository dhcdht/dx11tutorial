/********************************************************************
	created:	2012/04/24
	created:	24:4:2012   19:36
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial11\bitmapClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial11
	file base:	bitmapClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "bitmapClass.h"

BitmapClass::BitmapClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_texture = 0;
}

BitmapClass::BitmapClass( const BitmapClass &aBitmapClass )
{

}

BitmapClass::~BitmapClass()
{

}

bool BitmapClass::initialize( 
	ID3D11Device *aD3DDevice, int aWidth, int aHeight,
	WCHAR *aTextureFileName, 
	int aBitmapWidth, int aBitmapHeight )
{
	bool result;

	m_screenWidth = aWidth;
	m_screenHeight = aHeight;

	m_bitmapWidth = aBitmapWidth;
	m_bitmapHeight = aBitmapHeight;

	m_previousPosX = -1;
	m_previousPosY = -1;

	result = initializeBuffers(aD3DDevice);
	if (!result)
	{
		return false;
	}

	result = loadTexture(aD3DDevice, aTextureFileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::shutdown()
{
	releaseTexture();

	shutdownBuffers();

	return ;
}

bool BitmapClass::render( ID3D11DeviceContext *aD3DDeviceContext, int aPositionX, int aPositionY )
{
	bool result;

	result = updateBuffers(aD3DDeviceContext, aPositionX, aPositionY);
	if (!result)
	{
		return false;
	}

	renderBuffers(aD3DDeviceContext);

	return true;
}

int BitmapClass::getIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* BitmapClass::getTexture()
{
	return m_texture->getTexture();
}

bool BitmapClass::initializeBuffers( ID3D11Device *aD3DDevice )
{
	VertexType *vertices;
	unsigned int *indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	m_vertexCount = 6;

	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned int[m_indexCount];
	if (!indices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType)) * m_vertexCount);

	for (int i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}

	//动态缓冲：
	// Usage=D3D11_USAGE_DYNAMIC
	// CPUAccessFlags=D3D11_CPU_ACCESS_WRITE
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//静态缓冲：
	// Usage=D3D11_USAGE_DEFAULT
	// CPUAccessFlags=0
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void BitmapClass::shutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return ;
}

bool BitmapClass::updateBuffers( 
	ID3D11DeviceContext *aD3DDeviceContext, 
	int aPositionX,int aPositionY )
{
	float left, right, top, bottom;
	VertexType *vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType *verticesPtr;
	HRESULT result;

	if (m_previousPosX == aPositionX && m_previousPosY == aPositionY)
	{
		return true;
	}

	m_previousPosX = aPositionX;
	m_previousPosY = aPositionY;
	
	//2D渲染时DX以屏幕中心为（0, 0），所以重新计算图片位置
	left = (float)((m_screenWidth / 2) * -1) + (float)aPositionX;
	right = left + (float)m_bitmapWidth;
	top = (float)(m_screenHeight / 2) - (float)aPositionY;
	bottom = top - (float)m_bitmapHeight;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	result = aD3DDeviceContext->Map(
		m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(false))
	{
		return false;
	}

	verticesPtr = (VertexType *)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType)) * m_vertexCount);

	aD3DDeviceContext->Unmap(m_vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}

void BitmapClass::renderBuffers( ID3D11DeviceContext *aD3DDeviceContext )
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	aD3DDeviceContext->IASetVertexBuffers(
		0, 1, &m_vertexBuffer, &stride, &offset);

	aD3DDeviceContext->IASetIndexBuffer(
		m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	aD3DDeviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return ;
}

bool BitmapClass::loadTexture( ID3D11Device *aD3DDevice, WCHAR *aTextureFileName )
{
	bool result;

	m_texture = new TextureClass;
	if (!m_texture)
	{
		return false;
	}

	result = m_texture->initialize(aD3DDevice, aTextureFileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::releaseTexture()
{
	if (m_texture)
	{
		m_texture->shutdown();
		delete m_texture;
		m_texture = 0;
	}

	return ;
}
