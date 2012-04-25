/********************************************************************
	created:	2012/04/25
	created:	25:4:2012   18:59
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\fontClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	fontClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef fontClass_h__
#define fontClass_h__

#include <d3d11.h>
#include <D3DX10math.h>
#include <fstream>
using namespace std;

#include "textureClass.h"

class FontClass
{
private:
	struct FontType 
	{
		float left, right;
		int size;
	};

	struct VertexType 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass &aFontClass);
	~FontClass();

	bool initialize(
		ID3D11Device *aD3DDevice, 
		char *aFontFileName, WCHAR *aTextureFileName);
	void shutdown();

	ID3D11ShaderResourceView* GetTexture();

	void buildVertexArray(
		void *vertices, char *sentence,
		float aDrawX, float aDrawY);

private:
	bool loadFontData(char *aFontFileName);
	void releaseFontData();
	bool loadTexture(
		ID3D11Device *aD3DDevice, WCHAR *aTextureFileName);
	void releaseTexture();

private:
	FontType *m_font;
	TextureClass *m_texture;
};

#endif // fontClass_h__