#include "pch.h"
#include "Figures.h"


//LineSegment
LineSegment::LineSegment(Point Start, Point End) : m_Start(Start), m_End(End) {};


void LineSegment::DrawFigure(CClientDC* canvas)
{
	canvas->MoveTo(m_Start.m_x, m_Start.m_y);
	canvas->LineTo(m_End.m_x, m_End.m_y);

}
Type LineSegment::FigureType()
{
	return Type::line;
}

//CArc
CArc::CArc(Point Start, Point End, Point Center, bool clock) : m_Start(Start), m_End(End), m_Center(Center), m_bClock(clock) {}
void CArc::DrawFigure(CClientDC* canvas)
{
	
	double start_angle = atan2(1. * (m_Center.m_y - m_Start.m_y), (m_Start.m_x - m_Center.m_x));
	double sweep_angle = atan2(1. * (m_Center.m_y - m_End.m_y), (m_End.m_x - m_Center.m_x));
	double Radius = sqrt(pow(m_End.m_x - m_Center.m_x, 2) + pow(m_End.m_y - m_Center.m_y, 2));
	if (m_bClock)
	{
		double temp_angle = start_angle;
		start_angle = sweep_angle;
		sweep_angle = temp_angle;
	}
	canvas->Arc(m_Center.m_x - Radius, m_Center.m_y - Radius, m_Center.m_x + Radius, m_Center.m_y + Radius, m_Center.m_x + Radius * cos(start_angle),
		m_Center.m_y - Radius * sin(start_angle), m_Center.m_x + Radius * cos(sweep_angle), m_Center.m_y - Radius * sin(sweep_angle));
}
Type CArc::FigureType()
{
	return Type::Arc;
}