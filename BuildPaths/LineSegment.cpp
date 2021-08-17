#include "pch.h"
#include "LineSegment.h"

LineSegment::LineSegment(Point start, Point end) : m_start(start), m_end(end) {};


const void LineSegment::DrawFigure(std::unique_ptr<iDrawer>& draw)
{
	draw->DrawLine(m_start, m_end);
}
const Type LineSegment::FigureType()
{
	return Type::line;
}
const void LineSegment::ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* Line = doc->NewElement("LineSegment");
	path->InsertEndChild(Line);
	//Создаем стартовую точку
	tinyxml2::XMLElement* StartPoint = doc->NewElement("StartPoint");
	Line->InsertEndChild(StartPoint);
	// создаем точку x
	tinyxml2::XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	StartPoint->InsertEndChild(xs);
	// создаем точку y
	tinyxml2::XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	StartPoint->InsertEndChild(ys);
	//Создаем конечную точку
	tinyxml2::XMLElement* FinishPoint = doc->NewElement("FinishPoint");
	Line->InsertEndChild(FinishPoint);
	// создаем точку x
	tinyxml2::XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	FinishPoint->InsertEndChild(xf);
	// создаем точку y
	tinyxml2::XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	FinishPoint->InsertEndChild(yf);
}
