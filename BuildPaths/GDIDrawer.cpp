#include "pch.h"
#include "GDIDrawer.h"

void GDIDrawer::DrawLine(Point start, Point end)
{
	m_dc->MoveTo(start.m_x, start.m_y);
	m_dc->LineTo(end.m_x, end.m_y);
}

void GDIDrawer::DrawArc(Point start, Point end, Point centerell)
{

	double start_angle = atan2(1. * (centerell.m_y - start.m_y), (start.m_x - centerell.m_x));
	double sweep_angle = atan2(1. * (centerell.m_y - end.m_y), (end.m_x - centerell.m_x));
	double Radius = sqrt(pow(end.m_x - centerell.m_x, 2) + pow(end.m_y - centerell.m_y, 2));

	m_dc->Arc(centerell.m_x - Radius, centerell.m_y - Radius, centerell.m_x + Radius, centerell.m_y + Radius, centerell.m_x + Radius * cos(start_angle),
		centerell.m_y - Radius * sin(start_angle), centerell.m_x + Radius * cos(sweep_angle), centerell.m_y - Radius * sin(sweep_angle));
}

