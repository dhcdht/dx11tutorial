/********************************************************************
	created:	2012/04/26
	created:	26:4:2012   19:50
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\textClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	textClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef textClass_h__
#define textClass_h__

#include "fontClass.h"
#include "fontShaderClass.h"

class TextClass
{
private:
	struct SentenceType 
	{
		ID3D11Buffer *vertexBuffer;
		ID3D11Buffer *indexBuffer;
		int vertexCount;
		int indexCount;
		int maxLength;
		float red;
		float green;
		float blue;
	};

	struct VertexType 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass &aTextClass);
	~TextClass();

	bool initialize(
		ID3D11Device *aD3DDevice, 
		ID3D11DeviceContext *aD3DDeviceContext,
		HWND aHwnd, int aWidth, int aHeight,
		D3DXMATRIX aBaseViewMatrix);
	void shutdown();
	bool render(
		ID3D11DeviceContext *aD3DDeviceContext,
		D3DXMATRIX aWorldMatrix, D3DXMATRIX aOrthoMatrix);

private:
	bool initializeSentence(
		SentenceType **aSentence,
		int aMaxLength, ID3D11Device *aD3DDevice);
	bool updateSentence(
		SentenceType *aSentence, 
		char *aText, int aPositionX, int aPositionY,
		float aRed, float aGreen, float aBlue, 
		ID3D11DeviceContext *aD3DDeviceContext);
	void releaseSentence(SentenceType **aSentence);
	bool renderSentence(
		ID3D11DeviceContext *aD3DDeviceContext,
		SentenceType *aSentence,
		D3DXMATRIX aWorldMatrix, D3DXMATRIX aOrthoMatrix);

private:
	FontClass *m_font;
	FontShaderClass *m_fontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;

	SentenceType *m_sentence1;
	SentenceType *m_sentence2;
};

#endif // textClass_h__