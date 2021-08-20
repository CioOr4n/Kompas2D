#include "pch.h"
#include "LineSegment.h"

LineSegment::LineSegment(Point start, Point end) 
	: m_start(start)
	, m_end(end) 
{};


void LineSegment::DrawFigure(iDrawer& draw)
{
	draw.DrawLine(m_start, m_end);
}


void LineSegment::ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* line = doc->NewElement("LineSegment");
	path->InsertEndChild(line);
	//������� ��������� �����
	tinyxml2::XMLElement* startPoint = doc->NewElement("StartPoint");
	line->InsertEndChild(startPoint);
	// ������� ����� x
	tinyxml2::XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	startPoint->InsertEndChild(xs);
	// ������� ����� y
	tinyxml2::XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	startPoint->InsertEndChild(ys);
	//������� �������� �����
	tinyxml2::XMLElement* finishPoint = doc->NewElement("FinishPoint");
	line->InsertEndChild(finishPoint);
	// ������� ����� x
	tinyxml2::XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	finishPoint->InsertEndChild(xf);
	// ������� ����� y
	tinyxml2::XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	finishPoint->InsertEndChild(yf);
}
