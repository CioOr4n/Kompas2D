#pragma once
#include "pch.h"
#include "LineController.h"
#include "LineSegment.h"

LineController::LineController(TypeElem elem, CBuildPathsDoc* pDoc)
	:m_build(elem)
	,m_pDoc(pDoc)
{};


void LineController::InputValue(TypeOfData type, int value)
{
	switch (type)
	{
	case TypeOfData::length:
	{
		m_length = value;
		m_bL = true;
	}
	break;
	case TypeOfData::angle:
	{
		m_angle = value;
		m_bA = true;
	}
	break;
	}
	Check();
}


void LineController::CalcLine()
{
	m_end.m_x = m_start.m_x + cos(m_angle * M_PI / 180) * m_length;
	m_end.m_y = m_start.m_y + sin(m_angle * M_PI / 180) * m_length;
	Point temp = m_pDoc->GetEndDoc();
	if (m_end.m_x < 0)
		m_end.m_x = 0;
	if (m_end.m_y < 0)
		m_end.m_y = 0;
	if (m_end.m_x > temp.m_x)
		m_end.m_x = temp.m_x;
	if (m_end.m_y > temp.m_y)
		m_end.m_y = temp.m_y;
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
			AfxMessageBox(_T("Введите длину и угол линии"));
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
	ListPath& listOfPath = m_pDoc->GetPaths();
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
		CalcLine();
		EndPoints();
		AddToPath(GetIndex());
	}

}


bool LineController::CheckStart() 
{
	ListPath& listOfPath = m_pDoc->GetPaths();
	bool result = false;
	//проверка на концы путей в области area пикселей и на не закончен ли данный путь
	for (auto& path : listOfPath)
	{
		Point temp = path.GetEndPath();
		if ((abs(m_start.m_x - temp.m_x) < area) && (abs(m_start.m_y - temp.m_y) < area))
		{
			m_start = temp;
			result = true;
		}
	}
	// проверка на начало в области area пикселей
	if ((m_start.m_x < area) && (m_start.m_y < area) && !result)
	{
		Path path;
		listOfPath.emplace_back(std::move(path));
		m_start.m_x = 0;
		m_start.m_y = 0;
		result =  true;
	}

		
	
	return result;
}