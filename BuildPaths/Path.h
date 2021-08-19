#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // ����� ��� �������� ����� ����
{
private:
	std::list<std::unique_ptr<iFigure>> m_path; // ��������� �����
	Point m_endPath;
public:
	void Add(std::unique_ptr<iFigure>, Point); // ���������� ������
	Point GetEndPath(); // ��������� ����� ����
	void Draw(iDrawer &); // ��������� ����� ����
	void ToXML(tinyxml2::XMLElement*, tinyxml2::XMLDocument*); // ������ � xml  
};