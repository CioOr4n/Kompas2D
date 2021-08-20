#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // ����� ��� �������� ����� ����
{
private:
	using FigurePtr = std::unique_ptr<iFigure>;
	using ListFigures = std::list<FigurePtr>;
	ListFigures m_path; // ��������� �����
	Point m_endPath;
public:
	void Add(FigurePtr, Point); // ���������� ������
	Point GetEndPath() ; // ��������� ����� ����
	void Draw(iDrawer &); // ��������� ����� ����
	void ToXML(tinyxml2::XMLElement*, tinyxml2::XMLDocument*); // ������ � xml  
};