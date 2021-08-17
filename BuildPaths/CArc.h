#pragma once


#include "Figures.h"
class CArc : public iFigure // класс Arc
{
private:
	Point m_start, m_end, m_center;
public:
	const virtual void DrawFigure(std::unique_ptr<iDrawer>& draw) override;
	const virtual Type FigureType() override;
	const virtual void ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) override;
	CArc(Point Start, Point End, Point Center);
	virtual ~CArc() override {};
};