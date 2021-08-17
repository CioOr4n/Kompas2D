#pragma once

#include "Figures.h"
#include "iDrawer.h"
class LineSegment : public iFigure
{
private:
	Point m_start, m_end;
public:
	const virtual void DrawFigure(std::unique_ptr<iDrawer>& draw) override;
	const virtual Type FigureType() override;
	const virtual void ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) override;
	LineSegment(Point Start, Point End);
	virtual ~LineSegment() override {};
};