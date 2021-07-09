#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include "Win32Render.h"

class RenderManager : public Win32Render
{
public:
	static void InitRenderManager(HWND hWnd);
}; 
#endif