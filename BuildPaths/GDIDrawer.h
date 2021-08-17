#pragma once
#include "iDrawer.h"
#include <afxwin.h>

class GDIDrawer :public iDrawer
{
private:
	CClientDC* m_dc;
public:
	virtual void DrawLine(Point, Point) override;
	virtual void DrawArc(Point, Point, Point) override;
	GDIDrawer(CClientDC* dc) 
	{
		m_dc = dc;
	}
};