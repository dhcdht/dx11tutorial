/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   22:33
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial5\textureClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial5
	file base:	textureClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef textureClass_h__
#define textureClass_h__

#include <d3d11.h>
#include <D3DX11tex.h>

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool initialize(ID3D11Device*, WCHAR*);
	void shutdown();

	ID3D11ShaderResourceView* getTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

#endif // textureClass_h__