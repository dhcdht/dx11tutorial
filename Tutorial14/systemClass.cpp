/********************************************************************
	created:	2012/03/21
	created:	21:3:2012   9:53
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial2\systemClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial2
	file base:	systemClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "systemClass.h"

SystemClass::SystemClass()
{
	m_input = NULL;
	m_graphics = NULL;
}

SystemClass::SystemClass( const SystemClass& )
{

}

SystemClass::~SystemClass()
{

}

bool SystemClass::initialize()
{
	bool result;
	int screenWidth = 0;
	int screenHeight = 0;
	initializeWindows(screenWidth, screenHeight);

	m_input = new InputClass;
	if (NULL == m_input)
	{
		return false;
	}
	result = m_input->initialize(
		m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"初始化输入设备失败", L"Error", MB_OK);
		return false;
	}

	m_graphics = new GraphicsClass;
	if (NULL == m_graphics)
	{
		return false;
	}
	
	result = m_graphics->initialize(screenWidth, screenHeight, m_hwnd);
	if (false == result)
	{
		return false;
	}

	return true;
}

void SystemClass::shutdown()
{
	if (NULL == m_graphics)
	{
		m_graphics->shutdown();
		delete m_graphics;
		m_graphics = NULL;
	}

	if (NULL == m_input)
	{
		m_input->shutdown();
		delete m_input;
		m_input = NULL;
	}

	shutdownWindows();

	return ;
}

void SystemClass::run()
{
	 MSG msg;
	 ZeroMemory(&msg, sizeof(MSG));

	 bool result;
	 bool done = false;
	 while(!done)
	 {
		 if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		 {
			 TranslateMessage(&msg);
			 DispatchMessage(&msg);
		 }

		 if (msg.message == WM_QUIT)
		 {
			 done = true;
		 }
		 else
		 {
			 result = frame();
			 if (!result)
			 {
				 done = true;
			 }
		 }

		 if (m_input->isEscapePressed() == true)
		 {
			 done = true;
		 }
	 }

	 return ;
}

bool SystemClass::frame()
{
	bool result;
	int mouseX, mouseY;

	result = m_input->frame();
	if (!result)
	{
		return false;
	}

	m_input->getMouseLocation(mouseX, mouseY);

	result = m_graphics->frame(mouseX, mouseY);
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::messageHandler( 
	HWND hwnd, UINT msg, 
	WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void SystemClass::initializeWindows( int &aWidth, int &aHeight )
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	applicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = L"Enging_dhc";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX); 

	RegisterClassEx(&wc);

	aWidth = GetSystemMetrics(SM_CXSCREEN);
	aHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned int)aWidth;
		dmScreenSettings.dmPelsHeight = (unsigned int)aHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL |
			DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		aWidth = 800;
		aHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - aWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - aHeight) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		m_applicationName, m_applicationName, 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, aWidth, aHeight,
		NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);

	return ;
}

void SystemClass::shutdownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	applicationHandle = NULL;

	return ;
}

LRESULT CALLBACK wndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

	default:
		{
			return applicationHandle->messageHandler(hwnd, msg, wParam, lParam);
		}
	}
}
