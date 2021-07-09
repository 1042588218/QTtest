#ifndef __OBJECT_H__
#define __OBJECT_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "CMessage.h"

class Object
{  
public:
	virtual void Draw() = 0;
	virtual ~Object(){}
	virtual void UpData() = 0;
};

#endif