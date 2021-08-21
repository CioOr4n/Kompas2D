#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <afxwin.h>
#include <vector>
#include <memory>
#include "tinyxml2.h"
#include "iDrawer.h"
#include "Coord.h"


enum class TypeElem {line2p, linela, arc3p,arc2p, none}; // перечисления для выбора фигур

class iFigure // интерфейс
{
public:
	virtual ~iFigure() {};
public:
	 virtual void DrawFigure(iDrawer &) = 0; // отрисовка фигуры
	 virtual void ToXml(tinyxml2::XMLElement*, tinyxml2::XMLDocument*) = 0;
};











