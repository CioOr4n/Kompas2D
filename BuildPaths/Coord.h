#pragma once
struct Point // координаты точек в структуре
{
	int m_x, m_y;
	bool operator==(const Point& p1)
	{
		return (p1.m_x == this->m_x && this->m_y == p1.m_y);
	}
};