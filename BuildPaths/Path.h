#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // ����� ��� �������� ����� ����
{

	std::list<std::unique_ptr<iFigure>> m_path; // ��������� �����
	Point m_endPath;
	bool m_bIsEnd = false;
public:

	void Add(std::unique_ptr<iFigure> path, Point end); // ���������� ������
	Point GetEndPath(); // ��������� ����� ����

	void Draw(std::unique_ptr<iDrawer>& draw); // ��������� ����� ����
	bool IsEnd(); // �������� �������� �� ����
	void ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc); // ������ � xml  
};