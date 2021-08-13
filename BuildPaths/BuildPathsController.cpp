#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "BuildPathsDoc.h"
#include "BuildPathsController.h"




//LineController
void LineController::AddToPath(Path* paths) // добавление в путь (Тут пока плохо, утечка памяти)
{
	
	LineSegment* Line = new LineSegment(m_Start, m_End);
	paths->Add(Line,m_End);
}

LineController::LineController(Point Start, Point End) : m_Start(Start), m_End(End) {  } // конструктор длины по 2 точкам
LineController::LineController(Point Start, int nLength, double dblAngle) //конструктор по начанльной точке углу и длине
{
	m_Start = Start;
	m_End.m_x = Start.m_x + cos(dblAngle * M_PI / 180) * nLength;
	m_End.m_y = Start.m_y + sin(dblAngle * M_PI / 180) * nLength;

}


//ArcController
void ArcController::AddToPath(Path* paths) // добавление в путь (Тут пока плохо, утечка памяти)
{
	CArc* arc = new CArc(m_Start, m_End, m_Center,m_clock);
	paths->Add(arc, m_End);

}

ArcController::ArcController(Point Start, Point End, Point Middle) // Конструктор по 3 точкам 
{
	m_Start = Start;
	m_End = End; 
	//вычисление центра окружности
	m_Center = calc3p(Start, End, Middle);

	//получение направления дуги
	if ((m_Start.m_x > Middle.m_x) && (Middle.m_x > m_End.m_x))
		if (Middle.m_y < m_Start.m_y)
			if (Middle.m_y > m_Center.m_y)
				m_clock = true;
			else
				m_clock = false;
		else if (Middle.m_y > m_Center.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_Start.m_x > Middle.m_x) && (Middle.m_x < m_End.m_x))
		if (m_Start.m_y > Middle.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_Start.m_x < Middle.m_x) && (Middle.m_x > m_End.m_x))
		if (Middle.m_y > m_Start.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_Start.m_x < Middle.m_x) && (Middle.m_x < m_End.m_x))
		if (Middle.m_y > m_Start.m_y)
			if (Middle.m_y > m_Center.m_y)
				m_clock = false;
			else
				m_clock = true;
		else if (Middle.m_y > m_Center.m_y)
			m_clock = false;
		else
			m_clock = true;
}
ArcController::ArcController( Point Start, Point End, double dblRadius, bool clock) // конструктор по 2 точкам и ридиусу
{
	m_Start = Start;
	m_End = End;
	m_clock = !clock;
	double d = sqrt(pow(m_Start.m_x - m_End.m_x, 2) + pow(m_Start.m_y - m_End.m_y, 2));
	double h = sqrt(dblRadius * dblRadius - (d / 2) * (d / 2));
	//получение центра окружности в зависимости от направления дуги, так как можно построить две дуги между двумя точками с заданным радиусом
	if (clock)
	{
		m_Center.m_x = m_Start.m_x + (m_End.m_x - m_Start.m_x) / 2 + h * (m_End.m_y - m_Start.m_y) / d;
		m_Center.m_y = m_Start.m_y + (m_End.m_y - m_Start.m_y) / 2 - h * (m_End.m_x - m_Start.m_x) / d;
		
	}
	else
	{
		m_Center.m_x = m_Start.m_x + (m_End.m_x - m_Start.m_x) / 2 - h * (m_End.m_y - m_Start.m_y) / d;
		m_Center.m_y = m_Start.m_y + (m_End.m_y - m_Start.m_y) / 2 + h * (m_End.m_x - m_Start.m_x) / d;
	}
	
	
}
// вычисления центра окружности для 3 точек
Point ArcController::calc3p(Point s, Point e, Point m)
{
	float k1 = (s.m_x + m.m_x) / 2;
	float k2 = (s.m_y + m.m_y) / 2;
	float k3 = (s.m_x + e.m_x) / 2;
	float k4 = (s.m_y + e.m_y) / 2;
	float a1 = m.m_x - s.m_x;
	float b1 = m.m_y - s.m_y;
	float c1 = k1 * a1 + k2 * b1;
	float a2 = e.m_x - s.m_x;
	float b2 = e.m_y - s.m_y;
	float c2 = k3 * a2 + k4 * b2;
	Point res;
	res.m_x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
	res.m_y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
	return res;
}

