#ifndef __WIN32RENDER_H__
#define __WIN32RENDER_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

class Win32Render
{
public:
	~Win32Render();
	static void SetHWND(HWND hWnd);
	static void InitRender();
	static HDC  GetRender();
	
protected:
	static HDC  m_hDC;
	static HWND m_hWnd;
};
#endif