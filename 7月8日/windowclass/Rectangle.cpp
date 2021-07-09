#include <cassert>
#include "Rectangle.h"

CRectangle::CRectangle(const RECT& rect)
{
	SetRect(rect);
}

CRectangle::CRectangle(LONG left, LONG top, LONG right, LONG bottom)
{
	SetRect(left, top, right, bottom);
}

void CRectangle::SetRect(const RECT& rect)
{
	m_Rect = rect;
}

void CRectangle::SetRect(LONG left, LONG top, LONG right, LONG bottom)
{
	m_Rect.left   = left;
	m_Rect.top    = top;
	m_Rect.right  = right;
	m_Rect.bottom = bottom;
}

RECT CRectangle::GetRect() const
{
	return m_Rect;
}

void CRectangle::Move(const RECT& rect)
{
	SetRect(rect);
}

void CRectangle::Move(LONG left, LONG top, LONG right, LONG bottom)
{
	SetRect(left, top, right, bottom);
}

void CRectangle::LoadModule(const Object* pObject)
{
	assert(pObject != NULL);

	m_ModuleContainer.push_back(pObject);
}

void CRectangle::UpData()
{
}

void CRectangle::Draw()
{
}
    

