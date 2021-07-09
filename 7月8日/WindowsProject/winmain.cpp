#define WIN32_LEAN_AND_MENA 

#include <windows.h>
#include <windowsx.h>

#define WINDOW_CLASS_NAME L"WINCLASS"


//回调函数，消息处理函数
LRESULT CALLBACK WinsowProc(HWND hwnd, 
	                        UINT msg, 
	                        WPARAM wparam, 
	                        LPARAM lparam);


int WINAPI WinMain(HINSTANCE hinstance, // 程序实例句柄
	               HINSTANCE hprevinstance, 
	               LPSTR lpcmdline, 
	               int ncmdshow)
{
	WNDCLASSEX winclass; //窗口类
	HWND       hwnd;
	MSG        msg;

	winclass.cbSize        = sizeof(WNDCLASSEX);
	winclass.style         = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc   = WinsowProc;
	winclass.cbClsExtra    = 0;
	winclass.cbWndExtra    = 0;
	winclass.hInstance     = hinstance;
	winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName  = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
		return 0;

	if (!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		L"My Window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		400, 400,
		NULL, NULL,
		hinstance,
		NULL)))
		return 0;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);

}

LRESULT CALLBACK WinsowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC         hdc;
	RECT        rect;

	switch (msg)
	{
	case WM_CREATE:
	{
		
		return 0;
	} break;
	case WM_PAINT:
	{
		hdc = GetDC(hwnd);
		TextOut(hdc, 100, 100, L"HHH", 3);
		ReleaseDC(hwnd, hdc);
		hdc = BeginPaint(hwnd, &ps);
		//MessageBox(NULL, L"Hello,World!", L"message box", MB_OKCANCEL);
		EndPaint(hwnd, &ps);
		//GetClientRect(hwnd, &rect);
		//ValidateRect(hwnd, &rect);
		return  0;
	}break;
	case WM_COMMAND:
	{

	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	default:break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}