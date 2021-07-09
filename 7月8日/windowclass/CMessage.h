#ifndef __MESSAGE_H__
#define __MESSAGE_H__
#include <cassert>
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <vector>

class IMessage
{
public:
	struct Message
	{
		Message(UINT m, void(*f)(HWND,WPARAM, LPARAM))
		{
			assert(f != 0);
			msg = m;
			fp  = f;
		}
		UINT     msg;
		void(*fp)(HWND,WPARAM, LPARAM);
	};

    virtual void AddMessage() = 0;
};

class CMessage : public IMessage
{
	
public:
	static void OnCreate (HWND hWnd, WPARAM wparam, LPARAM lparam);
	static void OnDestroy(HWND hWnd, WPARAM wparam, LPARAM lparam);
	static void OnPaint(HWND hWnd, WPARAM wparam, LPARAM lparam);
    static void OnLbuttonDown(HWND hWnd, WPARAM wparam, LPARAM lparam);
	static void OnRbuttonDown(HWND hWnd, WPARAM wparam, LPARAM lparam);
	static void OnCommand(HWND hWnd, WPARAM wparam, LPARAM lparam);
	virtual void AddMessage();

protected:
	static std::vector<Message> m_Messages;

};

#endif