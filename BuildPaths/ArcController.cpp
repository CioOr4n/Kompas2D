#include "pch.h"
#include "ArcController.h"

ArcController::ArcController(TypeElem elem, CBuildPathsDoc* pDoc)
	: m_build(elem)
	, m_pDoc(pDoc)
{};


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


void ArcController::InputValue(int rad, int clock)
{
	m_rad = rad;
	m_bR = true;
	m_clock = clock;
	m_bCl = true;
	Check();
}


bool ArcController::CheckStart()
{
	std::list<Path>& listOfPath = m_pDoc->GetPaths();
	bool result = false;
	// проверка на начало в области area пикселей
	if ((abs(m_start.m_x - area) < area) & (abs(m_start.m_y - area) < area))
	{
	 
		Path path;
	
		listOfPath.emplace_back(std::move(path));
		m_start.m_x = 0;
		m_start.m_y = 0;
		result = true;
	}
	else
		//проверка на концы путей в области area пикселей и на не закончен ли данный путь
		for (auto& path : listOfPath)
		{
		
			Point temp = path.GetEndPath();
			if ((abs(m_start.m_x - temp.m_x) < area) & (abs(m_start.m_y - temp.m_y) < area) )
			{
				m_start = temp;
				result =  true;
			}
		}

	return result;

}


void ArcController::AddToPath(Path& path)
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
	path.Add(std::make_unique<CArc>(m_start, m_end, m_center), end);

}


void ArcController::Check()
{

	if (m_bS & m_bM & m_bE)
	{
		EndPoints();

		m_center = Calc3p();
		CalcClock3p();
		AddToPath(GetIndex());
		return;
	}
	if (m_bS & m_bE & m_bR & m_bCl)
	{
		EndPoints();
	
		Calc2p();
		AddToPath(GetIndex());
		return;
	}
}


void ArcController::Calc2p() // конструктор по 2 точкам и ридиусу
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
Point ArcController::Calc3p()
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


void ArcController::CalcClock3p()
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

	Point endOfDoc = m_pDoc->GetEndDoc();
	if ((abs(m_end.m_x - endOfDoc.m_x) < area) && (abs(m_end.m_y - endOfDoc.m_y) < area))
	{
		m_end = endOfDoc;
	}

}


Path& ArcController::GetIndex()
{
	std::list<Path>& listOfPath = m_pDoc->GetPaths();
	for (auto& path : listOfPath)
	{
		Point temp = path.GetEndPath();
		if (m_start == temp)
			return path;
	}

}