/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:43
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\inputClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	inputClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef inputClass_h__
#define inputClass_h__

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void initialize();

	void keyDown(unsigned int aInput);
	void keyUp(unsigned int aInput);

	bool isKeyDown(unsigned int aKey);

private:
	bool m_keys[256];
};

#endif // inputClass_h__