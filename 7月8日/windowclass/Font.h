#ifndef __FONT_H__
#define __FONT_H__
#include "Object.h"

class CFont : public Object
{
public:
	explicit CFont(const RECT& rect);
	CFont(LONG left, LONG top, LONG right, LONG bottom);

	void SetRect(const RECT& rect);
	void SetRect(LONG left, LONG top, LONG right, LONG bottom);

	RECT GetRect() const;
	
	void Move(const RECT& rect);
	void Move(LONG left, LONG top, LONG right, LONG bottom);

	void UpData();

	void Draw();
private:
	RECT m_Rect;
};

#endif