#include "RenderManager.h"

void RenderManager::InitRenderManager(HWND hWnd)
{
	SetHWND(hWnd);
	InitRender();
}