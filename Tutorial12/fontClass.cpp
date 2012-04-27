/********************************************************************
	created:	2012/04/25
	created:	25:4:2012   19:07
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\fontClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	fontClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "fontClass.h"

FontClass::FontClass()
{
	m_font = 0;
	m_texture = 0;
}

FontClass::FontClass( const FontClass &aFontClass )
{

}

FontClass::~FontClass()
{

}

bool FontClass::initialize( 
	ID3D11Device *aD3DDevice, 
	char *aFontFileName, WCHAR *aTextureFileName )
{
	bool result;

	result = loadFontData(aFontFileName);
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

void FontClass::shutdown()
{
	releaseTexture();

	releaseFontData();

	return ;
}

ID3D11ShaderResourceView* FontClass::getTexture()
{
	return m_texture->getTexture();
}

void FontClass::buildVertexArray( void *vertices, char *sentence, float aDrawX, float aDrawY )
{
	VertexType *vertexPtr;
	int numLetters, index, letter;

	vertexPtr = (VertexType *)vertices;

	numLetters = (int)strlen(sentence);

	index = 0;

	for (int i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - ' ';

		if (0 == letter)
		{
			aDrawX = aDrawX + 3.0f;
		}
		else
		{
			vertexPtr[index].position = 
				D3DXVECTOR3(aDrawX, aDrawY, 0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = 
				D3DXVECTOR3(
				aDrawX + m_font[letter].size, 
				aDrawY-16, 
				0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = 
				D3DXVECTOR3(aDrawX, aDrawY-16, 0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].left, 1.0f);
			index++;


			vertexPtr[index].position = 
				D3DXVECTOR3(aDrawX, aDrawY, 0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = 
				D3DXVECTOR3(
				aDrawX+m_font[letter].size,
				aDrawY, 
				0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = 
				D3DXVECTOR3(
				aDrawX+m_font[letter].size,
				aDrawY-16,
				0.0f);
			vertexPtr[index].texture = 
				D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			aDrawX = aDrawX + m_font[letter].size + 1.0f;
		}
	}

	return ;
}

bool FontClass::loadFontData( char *aFontFileName )
{
	ifstream fin;
	char temp;

	m_font = new FontType[95];
	if (!m_font)
	{
		return false;
	}

	fin.open(aFontFileName);
	if (fin.fail())
	{
		return false;
	}

	for (int i = 0; i < 95; i++)
	{
		fin.get(temp);
		while (' ' != temp)
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (' ' != temp)
		{
			fin.get(temp);
		}

		fin >> m_font[i].left;
		fin >> m_font[i].right;
		fin >> m_font[i].size;
	}

	fin.close();

	return true;
}

void FontClass::releaseFontData()
{
	if (m_font)
	{
		delete[] m_font;
		m_font = 0;
	}

	return ;
}

bool FontClass::loadTexture( 
	ID3D11Device *aD3DDevice, WCHAR *aTextureFileName )
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

void FontClass::releaseTexture()
{
	if (m_texture)
	{
		m_texture->shutdown();
		delete m_texture;
		m_texture = 0;
	}

	return ;
}
