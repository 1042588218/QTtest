#include "CMessage.h"
#include "resource.h"

std::vector<CMessage::Message> CMessage::m_Messages;

void CMessage::AddMessage()
{
	m_Messages.push_back(Message(WM_CREATE, OnCreate));
	m_Messages.push_back(Message(WM_DESTROY, OnDestroy));
	m_Messages.push_back(Message(WM_PAINT, OnPaint));
	m_Messages.push_back(Message(WM_LBUTTONDOWN,OnLbuttonDown));
	m_Messages.push_back(Message(WM_RBUTTONDOWN,OnRbuttonDown));
	m_Messages.push_back(Message(WM_COMMAND, OnCommand));
}

void CMessage::OnCreate (HWND hWnd, WPARAM wparam, LPARAM lparamm)
{
}

void CMessage::OnDestroy(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	PostQuitMessage(0);	
}

void CMessage::OnPaint(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC         hdc;
	hdc = BeginPaint(hWnd, &ps);
		  EndPaint(hWnd, &ps);
}


void CMessage::OnLbuttonDown(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	int x = LOWORD(lparam);
	int y = HIWORD(lparam);
	PostMessage(hWnd, WM_RBUTTONDOWN, 0, 0);
	MessageBox(NULL, _T("aaaa"), _T("aaa"), NULL);
}

void CMessage::OnRbuttonDown(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	OutputDebugString(_T("WM_R≤‚ ‘"));
}

void CMessage::OnCommand(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	DWORD wim = LOWORD(wparam);

	switch(wim)
	{
	case ID_QUIT:
		{
			PostQuitMessage(0);
		}break;
	case ID_BUBBLESORT:
		{
		} break;
	default: break;
	}

}