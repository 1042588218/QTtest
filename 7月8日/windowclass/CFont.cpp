#include "Font.h"

CFont::CFont(const RECT& rect)
{
	SetRect(rect);
}

CFont::CFont(LONG left, LONG top, LONG right, LONG bottom)
{
	SetRect(left, top, right, bottom);
}

void CFont::SetRect(const RECT& rect)
{
	m_Rect = rect;
}

void CFont::SetRect(LONG left, LONG top, LONG right, LONG bottom)
{
	m_Rect.left   = left;
	m_Rect.top    = top;
	m_Rect.right  = right;
	m_Rect.bottom = bottom;
}

RECT CFont::GetRect() const
{
	return m_Rect;
}

void CFont::Move(const RECT& rect)
{
	SetRect(rect);

}

void CFont::Move(LONG left, LONG top, LONG right, LONG bottom)
{
	SetRect(left, top, right, bottom);
}

void CFont::UpData()
{
}

void CFont::Draw()
{
}
  
