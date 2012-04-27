/********************************************************************
	created:	2012/04/26
	created:	26:4:2012   20:08
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\textClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	textClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "textClass.h"

TextClass::TextClass()
{
	m_font = 0;
	m_fontShader = 0;

	m_sentence1 = 0;
	m_sentence2 = 0;
}

TextClass::TextClass( const TextClass &aTextClass )
{

}

TextClass::~TextClass()
{

}

bool TextClass::initialize( 
	ID3D11Device *aD3DDevice, 
	ID3D11DeviceContext *aD3DDeviceContext, 
	HWND aHwnd, int aWidth, int aHeight, 
	D3DXMATRIX aBaseViewMatrix )
{
	bool result;

	m_screenWidth = aWidth;
	m_screenHeight = aHeight;

	m_baseViewMatrix = aBaseViewMatrix;

	m_font = new FontClass;
	if (!m_font)
	{
		return false;
	}

	result = m_font->initialize(
		aD3DDevice, "./obj/fontdata.txt", L"./tex/font.dds");
	if (!result)
	{
		MessageBox(aHwnd, L"不能初始化字体对象", L"Error", MB_OK);
		return false;
	}

	m_fontShader = new FontShaderClass;
	if (!m_fontShader)
	{
		return false;
	}

	result = m_fontShader->initialize(aD3DDevice, aHwnd);
	if (!result)
	{
		MessageBox(aHwnd, L"不能初始化字体渲染对象", L"Error", MB_OK);
		return false;
	}

	result = initializeSentence(&m_sentence1, 16, aD3DDevice);
	if (!result)
	{
		return false;
	}

	result = updateSentence(
		m_sentence1, "Hello", 0, 100,
		0.0f, 1.0f, 1.0f, aD3DDeviceContext);
	if (!result)
	{
		return false;
	}

	result = initializeSentence(&m_sentence2, 16, aD3DDevice);
	if (!result)
	{
		return false;
	}

	result = updateSentence(
		m_sentence2, "Goodbye", 0, 300,
		1.0f, 0.0f, 1.0f, aD3DDeviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextClass::shutdown()
{
	releaseSentence(&m_sentence1);

	releaseSentence(&m_sentence2);

	if (m_fontShader)
	{
		m_fontShader->shutdown();
		delete m_fontShader;
		m_fontShader = 0;
	}

	if (m_font)
	{
		m_font->shutdown();
		delete m_font;
		m_font = 0;
	}

	return ;
}

bool TextClass::render( ID3D11DeviceContext *aD3DDeviceContext, D3DXMATRIX aWorldMatrix, D3DXMATRIX aOrthoMatrix )
{
	bool result;

	result = renderSentence(
		aD3DDeviceContext, m_sentence1, aWorldMatrix, aOrthoMatrix);
	if (!result)
	{
		return false;
	}

	result = renderSentence(
		aD3DDeviceContext, m_sentence2, aWorldMatrix, aOrthoMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::initializeSentence( 
	SentenceType **aSentence,
	int aMaxLength, ID3D11Device *aD3DDevice )
{
	VertexType *vertices;
	unsigned int *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	(*aSentence) = new SentenceType;
	if (!(*aSentence))
	{
		return false;
	}

	(*aSentence)->vertexBuffer = 0;
	(*aSentence)->indexBuffer = 0;

	(*aSentence)->maxLength = aMaxLength;

	(*aSentence)->vertexCount = 6 * aMaxLength;

	(*aSentence)->indexCount = (*aSentence)->vertexCount;

	vertices = new VertexType[(*aSentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned int[(*aSentence)->indexCount];
	if (!indices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * (*aSentence)->vertexCount));

	for (int i = 0; i < (*aSentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*aSentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&vertexBufferDesc, &vertexData, &(*aSentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * (*aSentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&indexBufferDesc, &indexData, &(*aSentence)->indexBuffer);
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

bool TextClass::updateSentence( 
	SentenceType *aSentence, char *aText, 
	int aPositionX, int aPositionY, 
	float aRed, float aGreen, float aBlue, 
	ID3D11DeviceContext *aD3DDeviceContext )
{
	int numLetters;
	VertexType *vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType *verticesPtr;

	aSentence->red = aRed;
	aSentence->green = aGreen;
	aSentence->blue = aBlue;

	numLetters = (int)strlen(aText);

	if (numLetters > aSentence->maxLength)
	{
		return false;
	}

	vertices = new VertexType[aSentence->vertexCount];
	if (!vertices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * aSentence->vertexCount));

	drawX = (float)(((m_screenWidth / 2) * -1) + aPositionX);
	drawY = (float)((m_screenHeight / 2) - aPositionY);

	m_font->buildVertexArray((void*)vertices, aText, drawX, drawY);

	result = aD3DDeviceContext->Map(
		aSentence->vertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0,
		&mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices,
		(sizeof(VertexType) * aSentence->vertexCount));

	aD3DDeviceContext->Unmap(aSentence->vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::releaseSentence( SentenceType **aSentence)
{
	if (*aSentence)
	{
		if ((*aSentence)->vertexBuffer)
		{
			(*aSentence)->vertexBuffer->Release();
			(*aSentence)->vertexBuffer = 0;
		}

		if ((*aSentence)->indexBuffer)
		{
			(*aSentence)->indexBuffer->Release();
			(*aSentence)->indexBuffer = 0;
		}

		delete (*aSentence);
		(*aSentence) = 0;
	}

	return ;
}

bool TextClass::renderSentence( 
	ID3D11DeviceContext *aD3DDeviceContext, 
	SentenceType *aSentence, 
	D3DXMATRIX aWorldMatrix, D3DXMATRIX aOrthoMatrix )
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;

	stride = sizeof(VertexType);
	offset = 0;

	aD3DDeviceContext->IASetVertexBuffers(
		0, 1, &aSentence->vertexBuffer, &stride, &offset);

	aD3DDeviceContext->IASetIndexBuffer(
		aSentence->indexBuffer, DXGI_FORMAT_R32_FLOAT, 0);

	aD3DDeviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pixelColor = D3DXVECTOR4(
		aSentence->red, aSentence->green, aSentence->blue,
		1.0f);

	result = m_fontShader->render(
		aD3DDeviceContext, aSentence->indexCount,
		aWorldMatrix, m_baseViewMatrix, aOrthoMatrix,
		m_font->GetTexture(), pixelColor);
	if (!result)
	{
		return false;
	}

	return true;
}
