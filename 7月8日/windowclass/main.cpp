#include "CWindows.h"

int     HotKeyId;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CWindow wnd;
	if(!wnd.Create())
		return -1;
	wnd.AddMessage();
	return wnd.MessagePump();

}