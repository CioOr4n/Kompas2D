#pragma once

#include "Figures.h"
#include "iDrawer.h"
class LineSegment : public iFigure
{
private:
	Point m_start, m_end;
public:
	LineSegment(Point, Point);
	virtual ~LineSegment() override {};
public:
	 virtual void DrawFigure(iDrawer &) override;
	 virtual Type FigureType() override;
	 virtual void ToXml(tinyxml2::XMLElement*, tinyxml2::XMLDocument*) override;

};