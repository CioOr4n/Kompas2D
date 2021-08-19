#pragma once
#define _USE_MATH_DEFINES

#include <corecrt_math_defines.h>

#include "Figures.h"
#include "BuildPathsDoc.h"


enum class TypeOfData { rad, length, angle,clock };

const int area = 10;

class iController
{
public: 
	virtual ~iController() {};
public: 
	virtual void AddToPath(Path&) = 0;
	virtual void AddPoint(Point) = 0;
	virtual void InputValue(TypeOfData, int) = 0;
};




