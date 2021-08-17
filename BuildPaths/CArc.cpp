#include "pch.h"
#include "CArc.h"

CArc::CArc(Point Start, Point End, Point Center) : m_start(Start), m_end(End), m_center(Center) {};

const void CArc::DrawFigure(std::unique_ptr<iDrawer>& draw)
{
	draw->DrawArc(m_start, m_end, m_center);
}
const Type CArc::FigureType()
{
	return Type::Arc;
}

const void CArc::ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* ArcSegment = doc->NewElement("Arc");

	path->InsertEndChild(ArcSegment);
	//Создаем стартовую точку
	tinyxml2::XMLElement* StartPoint = doc->NewElement("StartPoint");
	ArcSegment->InsertEndChild(StartPoint);
	// создаем точку x
	tinyxml2::XMLElement* xs = doc->NewElement("x");
	xs->SetText(m_start.m_x);
	StartPoint->InsertEndChild(xs);
	// создаем точку y
	tinyxml2::XMLElement* ys = doc->NewElement("y");
	ys->SetText(m_start.m_y);
	StartPoint->InsertEndChild(ys);
	//Создаем Центр дуги
	tinyxml2::XMLElement* CenterPoint = doc->NewElement("CenterPoint");
	ArcSegment->InsertEndChild(CenterPoint);
	// создаем точку x
	tinyxml2::XMLElement* xc = doc->NewElement("x");
	xc->SetText(m_center.m_x);
	CenterPoint->InsertEndChild(xc);
	// создаем точку y
	tinyxml2::XMLElement* yc = doc->NewElement("y");
	yc->SetText(m_center.m_y);
	CenterPoint->InsertEndChild(yc);
	//Создаем конечную точку
	tinyxml2::XMLElement* FinishPoint = doc->NewElement("FinishPoint");
	ArcSegment->InsertEndChild(FinishPoint);
	// создаем точку x
	tinyxml2::XMLElement* xf = doc->NewElement("x");
	xf->SetText(m_end.m_x);
	FinishPoint->InsertEndChild(xf);
	// создаем точку y
	tinyxml2::XMLElement* yf = doc->NewElement("y");
	yf->SetText(m_end.m_y);
	FinishPoint->InsertEndChild(yf);
}