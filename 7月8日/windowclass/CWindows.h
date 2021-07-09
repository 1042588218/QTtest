#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "CMessage.h"

class CWindow : public CMessage
{
public:
	CWindow();
	BOOL RegisterWindow();
	BOOL Create();
	int MessagePump();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		for(unsigned int index = 0; index < m_Messages.size(); ++index)
		{
			if(msg == m_Messages[index].msg)
			{
				m_Messages[index].fp(hWnd, wparam, lparam);
			}
		}
		return DefWindowProc(hWnd, msg, wparam, lparam);
	}

private:
	HWND       m_hWnd;
	HINSTANCE  m_hInstance;
	WNDCLASSEX m_WndClass;
	
};