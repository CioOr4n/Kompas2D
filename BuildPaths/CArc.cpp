#include "pch.h"
#include "CArc.h"

CArc::CArc(Point start, Point end, Point center) 
	: m_start(start)
	,m_end(end)
	,m_center(center) 
{};


void CArc::DrawFigure(iDrawer & draw)
{
	draw.DrawArc(m_start, m_end, m_center);
}


Type CArc::FigureType()
{
	return Type::Arc;
}


void CArc::ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* arcSegment = doc->NewElement("Arc");

	path->InsertEndChild(arcSegment);
	//Создаем стартовую точку
	tinyxml2::XMLElement* startPoint = doc->NewElement("startPoint");
	arcSegment->InsertEndChild(startPoint);
	// создаем точку x
	tinyxml2::XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	startPoint->InsertEndChild(xs);
	// создаем точку y
	tinyxml2::XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	startPoint->InsertEndChild(ys);
	//Создаем Центр дуги
	tinyxml2::XMLElement* centerPoint = doc->NewElement("centerPoint");
	arcSegment->InsertEndChild(centerPoint);
	// создаем точку x
	tinyxml2::XMLElement* xc = doc->NewElement("x");
	xc->SetText(m_center.m_x);
	centerPoint->InsertEndChild(xc);
	// создаем точку y
	tinyxml2::XMLElement* yc = doc->NewElement("y");
	yc->SetText(m_center.m_y);
	centerPoint->InsertEndChild(yc);
	//Создаем конечную точку
	tinyxml2::XMLElement* finishPoint = doc->NewElement("finishPoint");
	arcSegment->InsertEndChild(finishPoint);
	// создаем точку x
	tinyxml2::XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	finishPoint->InsertEndChild(xf);
	// создаем точку y
	tinyxml2::XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	finishPoint->InsertEndChild(yf);
}