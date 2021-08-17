#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // ����� ��� �������� ����� ����
{
private:
	Point m_EndDoc;
	std::list<std::unique_ptr<iFigure>> m_path; // ��������� �����
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End), m_bIsEnd(false) {}; // �����������
	void Add(std::unique_ptr<iFigure> path, Point end); // ���������� ������
	const Point GetEndPath(); // ��������� ����� ����

	const void Draw(std::unique_ptr<iDrawer>& draw); // ��������� ����� ����
	const bool IsEnd(); // �������� �������� �� ����
	const void ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc); // ������ � xml  
};