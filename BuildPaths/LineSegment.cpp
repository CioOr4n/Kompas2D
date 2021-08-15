#include "pch.h"
#include "LineSegment.h"
LineSegment::LineSegment(Point Start, Point End) : m_start(Start), m_end(End) {};


const void LineSegment::DrawFigure(std::shared_ptr <CClientDC> canvas)
{
	canvas->MoveTo(m_start.m_x, m_start.m_y);
	canvas->LineTo(m_end.m_x, m_end.m_y);

}
const Type LineSegment::FigureType()
{
	return Type::line;
}
const void LineSegment::ToXml(XMLElement* path, tinyxml2::XMLDocument* doc)
{
	XMLElement* Line = doc->NewElement("LineSegment");
	path->InsertEndChild(Line);
	//Создаем стартовую точку
	XMLElement* StartPoint = doc->NewElement("StartPoint");
	Line->InsertEndChild(StartPoint);
	// создаем точку x
	XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	StartPoint->InsertEndChild(xs);
	// создаем точку y
	XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	StartPoint->InsertEndChild(ys);
	//Создаем конечную точку
	XMLElement* FinishPoint = doc->NewElement("FinishPoint");
	Line->InsertEndChild(FinishPoint);
	// создаем точку x
	XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	FinishPoint->InsertEndChild(xf);
	// создаем точку y
	XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	FinishPoint->InsertEndChild(yf);
}
