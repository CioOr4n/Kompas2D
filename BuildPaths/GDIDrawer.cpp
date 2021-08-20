#include "pch.h"
#include "GDIDrawer.h"

#define _USE_MATH_DEFINES
#include <corecrt_math_defines.h>
void GDIDrawer::DrawLine(Point start, Point end)
{
	m_dc->MoveTo(start.m_x, start.m_y);
	m_dc->LineTo(end.m_x, end.m_y);
}


void GDIDrawer::DrawArc(Point start, Point end, Point centerell)
{
	double start_angle = atan2(1. * (centerell.m_y - start.m_y), (start.m_x - centerell.m_x));
	double sweep_angle = atan2(1. * (centerell.m_y - end.m_y), (end.m_x - centerell.m_x));
	double radius = sqrt(pow(end.m_x - centerell.m_x, 2) + pow(end.m_y - centerell.m_y, 2));

	m_dc->Arc(centerell.m_x - radius, centerell.m_y - radius, centerell.m_x + radius, centerell.m_y + radius, centerell.m_x + radius * cos(start_angle),
		centerell.m_y - radius * sin(start_angle), centerell.m_x + radius * cos(sweep_angle), centerell.m_y - radius * sin(sweep_angle));
}


GDIDrawer::GDIDrawer(CDC* dc)
	:m_dc(dc)
{};