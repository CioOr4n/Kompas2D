#pragma once

#include "Figures.h"

class LineSegment : public iFigure
{
private:
	Point m_start, m_end;
public:
	const virtual void DrawFigure(CClientDC* canvas) override;
	const virtual Type FigureType() override;
	const virtual void ToXml(XMLElement* path, tinyxml2::XMLDocument* doc) override;
	LineSegment(Point Start, Point End);
	virtual ~LineSegment() override {};
};