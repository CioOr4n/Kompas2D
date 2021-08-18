#pragma once
#include "pch.h"
#include "LineController.h"
#include "LineSegment.h"
LineController::LineController(TypeElem elem, CBuildPathsDoc* pDoc) : m_build(elem), m_pDoc(pDoc) {}
void LineController::InputValue(int length, int angle)
{
	m_length = length;
	m_bL = true;
	m_angle = angle;
	m_bA = true;
	Check();
}
void LineController::calcLine()
{
	m_end.m_x = m_start.m_x + cos(m_angle * M_PI / 180) * m_length;
	m_end.m_y = m_start.m_y + sin(m_angle * M_PI / 180) * m_length;
}

void LineController::AddPoint(Point p)
{
	switch (m_build)
	{
	case TypeElem::line2p:
	{
		if (m_bS)
		{
			m_end = p;
			m_bE = true;
		}
	}
	break;
	case TypeElem::linela:
	{
		if (m_bS)
		{
			AfxMessageBox(_T("Введите радиус и направление дуги"));
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

void LineController::EndPoints()
{

	Point endOfDoc = m_pDoc->GetEndDoc();
	if ((abs(m_end.m_x - endOfDoc.m_x) < area) && (abs(m_end.m_y - endOfDoc.m_y) < area))
	{
		m_end = endOfDoc;
	}

}
Path& LineController::GetIndex()
{
	std::list<Path>& listOfPath = m_pDoc->GetPaths();
	for (auto& path : listOfPath)
	{
		Point temp = path.GetEndPath();
		if (m_start == temp)
			return path;
	}
	
	
}

void LineController::AddToPath(Path & m_paths)
{
	m_bS = false;
	m_bL = false;
	m_bE = false;
	m_bA = false;
	m_paths.Add(std::make_unique<LineSegment>(m_start, m_end), m_end);
}

void LineController::Check()
{
	if (m_bS & m_bE)
	{
		EndPoints();
		
		AddToPath(GetIndex());
	}
	if (m_bS & m_bA & m_bL)
	{
		calcLine();
		EndPoints();
	
		AddToPath(GetIndex());
	}

}
bool LineController::CheckStart()
{
	std::list<Path>& listOfPath = m_pDoc->GetPaths();
	bool result = false;
	// проверка на начало в области area пикселей
	if ((abs(m_start.m_x - area) < area) & (abs(m_start.m_x - area) < area))
	{
		Path path;
		listOfPath.emplace_back(std::move(path));
		m_start.m_x = 0;
		m_start.m_y = 0;
		result =  true;
	}
	else
		//проверка на концы путей в области area пикселей и на не закончен ли данный путь
		for (auto& path: listOfPath)
		{	
			Point temp = path.GetEndPath();
			if ((abs(m_start.m_x - temp.m_x) < area) & (abs(m_start.m_y - temp.m_y) < area) )
			{
				m_start = temp;
				result = true;
			}
		}

	return result;

}