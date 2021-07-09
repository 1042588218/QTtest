#include "CWindows.h"
#include "RenderManager.h"
#include "resource.h"

#define WINDOW_CLASS_NAME "MyGameWindow"


CWindow::CWindow()
{
	m_hWnd = 0;
	m_hInstance = GetModuleHandle(NULL);
	ZeroMemory(&m_WndClass, sizeof(WNDCLASSEX));
}

BOOL CWindow::RegisterWindow()
{
	m_WndClass.cbSize        = sizeof(WNDCLASSEX);
	m_WndClass.style         = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc   = WindowProc;
	m_WndClass.cbClsExtra    = 0;
	m_WndClass.cbWndExtra    = 0;
	m_WndClass.hInstance     = m_hInstance;
	m_WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	m_WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WndClass.lpszMenuName  = MAKEINTRESOURCE(IDR_ALGORITHMSELECT);
	m_WndClass.lpszClassName = _T(WINDOW_CLASS_NAME);
	m_WndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	
	return RegisterClassEx(&m_WndClass);
}

BOOL CWindow::Create()
{
	if(!RegisterWindow())
		return FALSE;

	if(!(m_hWnd = CreateWindowEx(NULL,
		                         _T(WINDOW_CLASS_NAME),
							     _T(WINDOW_CLASS_NAME),
							     WS_OVERLAPPEDWINDOW,
							     100, 100,
							     800, 600,
							     NULL,
							     NULL, 
							     m_hInstance,
							     NULL)))
		return FALSE;


	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}
int CWindow::MessagePump()
{
	MSG msg;
	//ZeroMemory(&msg, sizeof(msg));

	while(GetMessage(&msg,0, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

