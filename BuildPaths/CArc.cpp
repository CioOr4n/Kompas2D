#include "pch.h"
#include "CArc.h"

CArc::CArc(Point Start, Point End, Point Center, bool clock) : m_start(Start), m_end(End), m_center(Center), m_bClock(clock) {}
const void CArc::DrawFigure(CClientDC* canvas)
{

	double start_angle = atan2(1. * (m_center.m_y - m_start.m_y), (m_start.m_x - m_center.m_x));
	double sweep_angle = atan2(1. * (m_center.m_y - m_end.m_y), (m_end.m_x - m_center.m_x));
	double Radius = sqrt(pow(m_end.m_x - m_center.m_x, 2) + pow(m_end.m_y - m_center.m_y, 2));

	canvas->Arc(m_center.m_x - Radius, m_center.m_y - Radius, m_center.m_x + Radius, m_center.m_y + Radius, m_center.m_x + Radius * cos(start_angle),
		m_center.m_y - Radius * sin(start_angle), m_center.m_x + Radius * cos(sweep_angle), m_center.m_y - Radius * sin(sweep_angle));
}
const Type CArc::FigureType()
{
	return Type::Arc;
}

const void CArc::ToXml(XMLElement* path, tinyxml2::XMLDocument* doc)
{
	XMLElement* ArcSegment = doc->NewElement("Arc");
	//добавляем аттрибут направление дуги
	ArcSegment->SetAttribute("Clock", m_bClock);
	path->InsertEndChild(ArcSegment);
	//Создаем стартовую точку
	XMLElement* StartPoint = doc->NewElement("StartPoint");
	ArcSegment->InsertEndChild(StartPoint);
	// создаем точку x
	XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	StartPoint->InsertEndChild(xs);
	// создаем точку y
	XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	StartPoint->InsertEndChild(ys);
	//Создаем Центр дуги
	XMLElement* CenterPoint = doc->NewElement("CenterPoint");
	ArcSegment->InsertEndChild(CenterPoint);
	// создаем точку x
	XMLElement* xc = doc->NewElement("x");
	xc->SetText(m_center.m_x);
	CenterPoint->InsertEndChild(xc);
	// создаем точку y
	XMLElement* yc = doc->NewElement("y");
	yc->SetText(m_center.m_y);
	CenterPoint->InsertEndChild(yc);
	//Создаем конечную точку
	XMLElement* FinishPoint = doc->NewElement("FinishPoint");
	ArcSegment->InsertEndChild(FinishPoint);
	// создаем точку x
	XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	FinishPoint->InsertEndChild(xf);
	// создаем точку y
	XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	FinishPoint->InsertEndChild(yf);
}