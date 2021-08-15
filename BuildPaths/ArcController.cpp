#include "pch.h"
#include "ArcController.h"
ArcController::ArcController(TypeElem Elem, CBuildPathsDoc* pDoc) : m_build(Elem), m_pDoc(pDoc) {}
void ArcController::AddPoint(Point p)
{
	switch (m_build)
	{
	case TypeElem::arc3p:
	{
		if (m_bS & m_bM)
		{
			m_end = p;
			m_bE = true;

		}
		else  if (m_bS)
		{
			m_middle = p;
			m_bM = true;
			return;
		}

	}
	break;
	case TypeElem::arc2p:
	{
		if (m_bE & m_bS)
		{
			AfxMessageBox(_T("Введите радиус и направление дуги"));
			return;
		}
		else if (m_bS)
		{
			m_end = p;
			m_bE = true;
			return;
		}
	}
	break;

	}
	if (!m_bS)
	{
		m_start = p;
		if (CheckStart())
			m_bS = true;
		else
			AfxMessageBox(_T("Начинайте с начала или с конца созданного пути"));
	}
	Check();

}

bool ArcController::CheckStart()
{


	// проверка на начало в области 10 пикселей
	if ((abs(m_start.m_x - 10) < 10) & (abs(m_start.m_x - 10) < 10))
	{
		CRect rc;
		POSITION sd = m_pDoc->GetFirstViewPosition();
		m_pDoc->GetNextView(sd)->GetClientRect(&rc);
		Point temp;
		temp.m_x = rc.right - 1;
		temp.m_y = rc.bottom - 1;
		Path path(temp);
		m_pDoc->Paths.emplace_back(std::move(path));
		m_start.m_x = 0;
		m_start.m_y = 0;
		return true;
	}
	else
		//проверка на концы путей в области 10 пикселей и на не закончен ли данный путь
		for (int i = 0; i < m_pDoc->Paths.size(); i++)
		{

			Point temp = m_pDoc->Paths[i].GetEndPath();
			if ((abs(m_start.m_x - temp.m_x) < 10) & (abs(m_start.m_y - temp.m_y) < 10) & !m_pDoc->Paths[i].IsEnd())
			{
				m_start = temp;
				return true;
			}
		}

	return false;

}


void ArcController::SetRad(int rad)
{
	m_rad = rad;
	m_bR = true;
	Check();
}

void ArcController::SetClock(bool clock)
{
	m_clock = clock;
	m_bCl = true;
	Check();
}


void ArcController::AddToPath(Path* path)
{
	Point end = m_end;
	if (m_clock)
	{
		std::swap(m_start, m_end);
		end = m_start;

	}
	m_bS = false;
	m_bM = false;
	m_bE = false;
	m_bCl = false;
	m_bR = false;
	path->Add(std::make_unique<CArc>(m_start, m_end, m_center, m_clock), end);

}

void ArcController::Check()
{

	if (m_bS & m_bM & m_bE)
	{
		EndPoints();
		int index = GetIndex();

		m_center = calc3p();
		calcClock3p();
		AddToPath(&m_pDoc->Paths[index]);
		return;
	}
	if (m_bS & m_bE & m_bR & m_bCl)
	{
		EndPoints();
		int index = GetIndex();
		calc2p();
		AddToPath(&m_pDoc->Paths[index]);
		return;
	}
}


void ArcController::calc2p() // конструктор по 2 точкам и ридиусу
{

	m_clock = !m_clock;
	double d = sqrt(pow(m_start.m_x - m_end.m_x, 2) + pow(m_start.m_y - m_end.m_y, 2));
	while (m_rad < d / 2)
	{
		m_rad++;
	}
	double h = sqrt(m_rad * m_rad - (d / 2) * (d / 2));

	//получение центра окружности в зависимости от направления дуги, так как можно построить две дуги между двумя точками с заданным радиусом
	if (!m_clock)
	{
		m_center.m_x = m_start.m_x + (m_end.m_x - m_start.m_x) / 2 + h * (m_end.m_y - m_start.m_y) / d;
		m_center.m_y = m_start.m_y + (m_end.m_y - m_start.m_y) / 2 - h * (m_end.m_x - m_start.m_x) / d;

	}
	else
	{
		m_center.m_x = m_start.m_x + (m_end.m_x - m_start.m_x) / 2 - h * (m_end.m_y - m_start.m_y) / d;
		m_center.m_y = m_start.m_y + (m_end.m_y - m_start.m_y) / 2 + h * (m_end.m_x - m_start.m_x) / d;
	}


}
// вычисления центра окружности для 3 точек
Point ArcController::calc3p()
{
	float k1 = (m_start.m_x + m_middle.m_x) / 2;
	float k2 = (m_start.m_y + m_middle.m_y) / 2;
	float k3 = (m_start.m_x + m_end.m_x) / 2;
	float k4 = (m_start.m_y + m_end.m_y) / 2;
	float a1 = m_middle.m_x - m_start.m_x;
	float b1 = m_middle.m_y - m_start.m_y;
	float c1 = k1 * a1 + k2 * b1;
	float a2 = m_end.m_x - m_start.m_x;
	float b2 = m_end.m_y - m_start.m_y;
	float c2 = k3 * a2 + k4 * b2;
	Point res;
	res.m_x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
	res.m_y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
	return res;
}


void ArcController::calcClock3p()
{

	if ((m_start.m_x > m_middle.m_x) && (m_middle.m_x > m_end.m_x))
		if (m_middle.m_y < m_start.m_y)
			if (m_middle.m_y > m_center.m_y)
				m_clock = true;
			else
				m_clock = false;
		else if (m_middle.m_y > m_center.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_start.m_x > m_middle.m_x) && (m_middle.m_x < m_end.m_x))
		if (m_start.m_y > m_middle.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_start.m_x < m_middle.m_x) && (m_middle.m_x > m_end.m_x))
		if (m_middle.m_y > m_start.m_y)
			m_clock = true;
		else
			m_clock = false;
	else if ((m_start.m_x < m_middle.m_x) && (m_middle.m_x < m_end.m_x))
		if (m_middle.m_y > m_start.m_y)
			if (m_middle.m_y > m_center.m_y)
				m_clock = false;
			else
				m_clock = true;
		else if (m_middle.m_y > m_center.m_y)
			m_clock = false;
		else
			m_clock = true;
}

void ArcController::EndPoints()
{

	Point EndOfDoc = m_pDoc->Paths[0].GetEndDoc();
	if ((abs(m_end.m_x - EndOfDoc.m_x) < 10) && (abs(m_end.m_x - EndOfDoc.m_y) < 10))
	{
		m_end = EndOfDoc;
	}

}
int ArcController::GetIndex()
{

	for (int i = 0; i < m_pDoc->Paths.size(); i++)
	{
		Point temp = m_pDoc->Paths[i].GetEndPath();
		if ((m_start.m_x == temp.m_x) & (m_start.m_y == temp.m_y))
			return i;
	}
	return -1;
}