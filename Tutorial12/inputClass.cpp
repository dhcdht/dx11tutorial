/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   13:07
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\inputClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	inputClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "inputClass.h"

InputClass::InputClass()
{

}

InputClass::InputClass( const InputClass& )
{

}

InputClass::~InputClass()
{

}

void InputClass::initialize()
{
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}

	return ;
}

void InputClass::keyDown( unsigned int aInput )
{
	m_keys[aInput] = true;

	return ;
}

void InputClass::keyUp( unsigned int aInput )
{
	m_keys[aInput] = false;

	return ;
}

bool InputClass::isKeyDown( unsigned int aKey)
{
	return m_keys[aKey];
}
