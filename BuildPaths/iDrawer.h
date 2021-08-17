#pragma once
#include "Coord.h"
#include <memory>
class iDrawer
{
public:
	virtual void DrawLine(Point, Point) = 0;
	virtual void DrawArc(Point, Point, Point) = 0;
};