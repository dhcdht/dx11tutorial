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

#include "graphicsClass.h"

InputClass::InputClass()
{
	m_directInput = 0;
	m_keyBoard = 0;
	m_mouse = 0;
}

InputClass::InputClass( const InputClass& other )
{

}

InputClass::~InputClass()
{

}

bool InputClass::initialize( 
	HINSTANCE aHinstance, HWND aHwnd, 
	int aWidth, int aHeight )
{
	HRESULT result;
	
	if (FULL_SCREEN)
	{
		m_screenWidth = aWidth;
		m_screenHeight = aHeight;
	}
	else
	{
		m_screenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	}

	POINT pt;

	GetCursorPos(&pt);

	m_mouseX = pt.x;
	m_mouseY = pt.y;

	result = DirectInput8Create(aHinstance, 
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(
		GUID_SysKeyboard, &m_keyBoard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyBoard->SetCooperativeLevel(
		aHwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyBoard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(
		GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetCooperativeLevel(
		aHwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void InputClass::shutdown()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	if (m_keyBoard)
	{
		m_keyBoard->Unacquire();
		m_keyBoard->Release();
		m_keyBoard = 0;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return ;
}

bool InputClass::frame()
{
	bool result;

	result = readKeyBoard();
	if (!result)
	{
		return false;
	}

	result = readMouse();
	if (!result)
	{
		return false;
	}

	ProcessInput();

	return true;
}

bool InputClass::readKeyBoard()
{
	HRESULT result;

	result = m_keyBoard->GetDeviceState(
		sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if (DIERR_INPUTLOST == result || DIERR_NOTACQUIRED == result)
		{
			m_keyBoard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputClass::readMouse()
{
	HRESULT result;

	result = m_mouse->GetDeviceState(
		sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if (DIERR_INPUTLOST == result || DIERR_NOTACQUIRED == result)
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput()
{
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	m_mouseX = m_mouseX < 0 ? 0 : m_mouseX;
	m_mouseY = m_mouseY < 0 ? 0 : m_mouseY;

	m_mouseX = m_mouseX > m_screenWidth ? m_screenWidth : m_mouseX;
	m_mouseY = m_mouseY > m_screenHeight ? m_screenHeight : m_mouseY;

	return ;
}

bool InputClass::isEscapePressed()
{
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

void InputClass::getMouseLocation( int &posX, int &posY )
{
	posX = m_mouseX;
	posY = m_mouseY;

	return ;
}
