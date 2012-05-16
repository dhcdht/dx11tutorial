/********************************************************************
	created:	2012/05/05
	created:	5:5:2012   13:33
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial17\textureArrayClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial17
	file base:	textureArrayClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "textureArrayClass.h"

TextureArrayClass::TextureArrayClass()
{
	m_textures[0] = 0;
	m_textures[1] = 0;
}

TextureArrayClass::TextureArrayClass( const TextureArrayClass &other )
{

}

TextureArrayClass::~TextureArrayClass()
{

}

bool TextureArrayClass::initialize( 
	ID3D11Device *aD3DDevice, 
	WCHAR *aTexFileName1, WCHAR *aTexFileName2 )
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(
		aD3DDevice, aTexFileName1, NULL, NULL, &m_textures[0],
		NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = D3DX11CreateShaderResourceViewFromFile(
		aD3DDevice, aTexFileName2, NULL, NULL, &m_textures[1],
		NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureArrayClass::shutdown()
{
	if (m_textures[0])
	{
		m_textures[0]->Release();
		m_textures[0] = 0;
	}

	if (m_textures[1])
	{
		m_textures[1]->Release();
		m_textures[1] = 0;
	}

	return ;
}

ID3D11ShaderResourceView** TextureArrayClass::getTextureArray()
{
	return m_textures;
}
