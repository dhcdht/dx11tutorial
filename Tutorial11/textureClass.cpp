/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   22:35
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial5\textureClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial5
	file base:	textureClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "textureClass.h"

TextureClass::TextureClass()
{
	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}

bool TextureClass::initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(
		device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureClass::shutdown()
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::getTexture()
{
	return m_texture;
}