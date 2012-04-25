/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   19:58
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\modelClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	modelClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "modelClass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;

	m_texture = NULL;
}

ModelClass::ModelClass( const ModelClass &aModelClass )
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::initialize( ID3D11Device *aD3DDevice, WCHAR *aFileName )
{
	bool result;

	result = initializeBuffers(aD3DDevice);
	
	result = loadTexture(aD3DDevice, aFileName);
	if (!result)
	{
		return false;
	}

	return result;
}

void ModelClass::shutdown()
{
	releaseTexture();

	shutdownBuffers();

	return ;
}

void ModelClass::render( ID3D11DeviceContext *aD3DDeviceContext )
{
	renderBuffers(aD3DDeviceContext);

	return ;
}

int ModelClass::getIndexCount()
{
	return m_indexCount;
}

bool ModelClass::initializeBuffers( ID3D11Device *aD3DDevice )
{
	VertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	m_vertexCount = 3;

	m_indexCount = 3;

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = aD3DDevice->CreateBuffer(
		&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}
		
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void ModelClass::shutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}

	return ;
}

void ModelClass::renderBuffers( ID3D11DeviceContext *aD3DDeviceContext )
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

ID3D11ShaderResourceView* ModelClass::getTexture()
{
	return m_texture->getTexture();
}

bool ModelClass::loadTexture( ID3D11Device *aD3DDevice, WCHAR *aFileName )
{
	bool result;

	m_texture = new TextureClass;
	if (NULL == m_texture)
	{
		return false;
	}

	result = m_texture->initialize(aD3DDevice, aFileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::releaseTexture()
{
	if (NULL != m_texture)
	{
		m_texture->shutdown();
		delete m_texture;
		m_texture = NULL;
	}

	return ;
}
