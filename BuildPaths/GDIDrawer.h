#pragma once
#include "iDrawer.h"
#include <afxwin.h>

class GDIDrawer :public iDrawer
{
private:
	CDC* m_dc;
public:
	GDIDrawer(CDC*);
public:
	virtual void DrawLine(Point, Point) override;
	virtual void DrawArc(Point, Point, Point) override;
};