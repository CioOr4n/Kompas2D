#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <afxwin.h>
#include <vector>
#include <memory>
#include "tinyxml2.h"
#include "iDrawer.h"
#include "Coord.h"


enum class TypeElem {line2p, linela, arc3p,arc2p}; // перечисления для выбора фигур
enum class Type { line, Arc }; // перечисление для вид фигур

class iFigure // интерфейс
{
public:
	const virtual void DrawFigure(std::unique_ptr<iDrawer>& draw) = 0; // отрисовка фигуры
	const virtual Type FigureType() = 0; // тип фигуры
	const virtual void ToXml(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) = 0;
	virtual ~iFigure() {};
};











