#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <afxwin.h>
#include <vector>
#include <memory>
#include "tinyxml2.h"

using namespace tinyxml2;
enum class TypeElem {line2p, linela, arc3p,arc2p}; // ������������ ��� ������ �����
enum class Type { line, Arc }; // ������������ ��� ��� �����
struct Point // ���������� ����� � ���������
{
	int m_x, m_y;
};

class iFigure // ���������
{
public:
	const virtual void DrawFigure(std::shared_ptr < CClientDC>) = 0; // ��������� ������
	const virtual Type FigureType() = 0; // ��� ������
	const virtual void ToXml(XMLElement* path, tinyxml2::XMLDocument* doc) = 0;
	virtual ~iFigure() {};
};











