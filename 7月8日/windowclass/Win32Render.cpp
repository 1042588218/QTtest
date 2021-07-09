#include <cassert>
#include "Win32Render.h"

HDC  Win32Render::m_hDC = NULL;
HWND Win32Render::m_hWnd = NULL;

Win32Render::~Win32Render()
{
	assert(m_hWnd != NULL);

	if (m_hDC != NULL)
	{
		ReleaseDC(m_hWnd, m_hDC);
	}
}

void Win32Render::SetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}

void Win32Render::InitRender()
{
	assert(m_hWnd != NULL);
	m_hDC = GetDC(m_hWnd);
	assert(m_hDC != NULL);
}

HDC Win32Render::GetRender()
{
	assert(m_hDC != NULL);
	return m_hDC;
}