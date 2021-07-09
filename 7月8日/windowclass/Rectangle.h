#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include <vector>
#include "Object.h"

class CRectangle : public Object
{
public:
	explicit CRectangle(const RECT& rect);

	CRectangle(LONG left, LONG top, LONG right, LONG bottom);
	
	void SetRect(const RECT& rect);
	void SetRect(LONG left, LONG top, LONG right, LONG bottom);

	RECT GetRect() const;
	
	void Move(const RECT& rect);
	void Move(LONG left, LONG top, LONG right, LONG bottom);
	
	void LoadModule(const Object* pObject);

	void UpData();

	void Draw();
private:
	RECT                 m_Rect;
	std::vector<const Object*> m_ModuleContainer;
};

#endif