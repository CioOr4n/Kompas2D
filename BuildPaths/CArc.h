#pragma once


#include "Figures.h"
class CArc : public iFigure // класс Arc
{
private:
	Point m_start, m_end, m_center;
public:
	CArc(Point, Point, Point);
	virtual ~CArc() override {};
public:
	 virtual void DrawFigure(iDrawer &) override;
	 virtual Type FigureType() override;
	 virtual void ToXml(tinyxml2::XMLElement*, tinyxml2::XMLDocument*) override;
};