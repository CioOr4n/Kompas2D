#pragma once

#include "Figures.h"

class Path // ����� ��� �������� ����� ����
{
private:
	Point m_EndDoc;
	std::vector< std::unique_ptr<iFigure>> m_path; // ��������� �����
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End), m_bIsEnd(false) {}; // �����������
	void Add(std::unique_ptr<iFigure> path, Point end); // ���������� ������
	const Point GetEndPath(); // ��������� ����� ����
	const Point GetEndDoc();
	const void Draw(std::shared_ptr <CClientDC>); // ��������� ����� ����
	const bool IsEnd(); // �������� �������� �� ����
	const void ToXML(XMLElement* path, tinyxml2::XMLDocument* doc); // ������ � xml  

};