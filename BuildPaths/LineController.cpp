#pragma once
#include "pch.h"
#include "LineController.h"
#include "LineSegment.h"
LineController::LineController(TypeElem Elem, CBuildPathsDoc* pDoc) : m_build(Elem), m_pDoc(pDoc) {}
void LineController::calcLine()
{
	m_end.m_x = m_start.m_x + cos(m_angle * M_PI / 180) * m_length;
	m_end.m_y = m_start.m_y + sin(m_angle * M_PI / 180) * m_length;
}
void LineController::SetLength(int length)
{
	m_length = length;
	m_bL = true;
	Check();
}
void LineController::SetAngle(int angle)
{
	m_angle = angle;
	m_bA = true;
	Check();
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

	Point EndOfDoc = m_pDoc->Paths[0].GetEndDoc();
	if ((abs(m_end.m_x - EndOfDoc.m_x) < 10) && (abs(m_end.m_x - EndOfDoc.m_y) < 10))
	{
		m_end = EndOfDoc;
	}

}
int LineController::GetIndex()
{

	for (int i = 0; i < m_pDoc->Paths.size(); i++)
	{
		Point temp = m_pDoc->Paths[i].GetEndPath();
		if ((m_start.m_x == temp.m_x) & (m_start.m_y == temp.m_y))
			return i;
	}
	return -1;
}

void LineController::AddToPath(Path* paths)
{
	m_bS = false;
	m_bL = false;
	m_bE = false;
	m_bA = false;
	paths->Add(std::make_unique<LineSegment>(m_start, m_end), m_end);
}

void LineController::Check()
{
	if (m_bS & m_bE)
	{
		EndPoints();
		int index = GetIndex();
		AddToPath(&m_pDoc->Paths[index]);
	}
	if (m_bS & m_bA & m_bL)
	{
		calcLine();
		EndPoints();
		int index = GetIndex();
		AddToPath(&m_pDoc->Paths[index]);
	}

}
bool LineController::CheckStart()
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