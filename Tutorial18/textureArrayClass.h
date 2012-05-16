/********************************************************************
	created:	2012/05/05
	created:	5:5:2012   13:28
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial17\textureArrayClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial17
	file base:	textureArrayClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef textureArrayClass_h__
#define textureArrayClass_h__

#include <d3d11.h>
#include <D3DX11tex.h>

class TextureArrayClass
{
public:
	TextureArrayClass();
	TextureArrayClass(const TextureArrayClass &other);
	~TextureArrayClass();

	bool initialize(
		ID3D11Device *aD3DDevice, 
		WCHAR *aTexFileName1, WCHAR *aTexFileName2);
	void shutdown();

	ID3D11ShaderResourceView** getTextureArray();

private:
	ID3D11ShaderResourceView *m_textures[2];
};

#endif // textureArrayClass_h__