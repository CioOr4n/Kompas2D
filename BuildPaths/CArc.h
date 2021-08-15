#pragma once


#include "Figures.h"

class CArc : public iFigure // класс Arc
{
private:
	Point m_start, m_end, m_center;
	bool m_bClock;
public:
	const virtual void DrawFigure(std::shared_ptr < CClientDC>) override;
	const virtual Type FigureType() override;
	const virtual void ToXml(XMLElement* path, tinyxml2::XMLDocument* doc) override;
	CArc(Point Start, Point End, Point Center, bool clock);
	virtual ~CArc() override {};
};