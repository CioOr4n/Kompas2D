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
	//������� ��������� �����
	XMLElement* StartPoint = doc->NewElement("StartPoint");
	Line->InsertEndChild(StartPoint);
	// ������� ����� x
	XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	StartPoint->InsertEndChild(xs);
	// ������� ����� y
	XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	StartPoint->InsertEndChild(ys);
	//������� �������� �����
	XMLElement* FinishPoint = doc->NewElement("FinishPoint");
	Line->InsertEndChild(FinishPoint);
	// ������� ����� x
	XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	FinishPoint->InsertEndChild(xf);
	// ������� ����� y
	XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	FinishPoint->InsertEndChild(yf);
}
