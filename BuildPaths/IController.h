#pragma once
#define _USE_MATH_DEFINES

#include <corecrt_math_defines.h>

#include "Figures.h"
#include "BuildPathsDoc.h"


const int area = 10;
class iController
{
public: 
	virtual void AddToPath(Path&) = 0;
	virtual void AddPoint(Point) = 0;
	virtual void InputValue(int, int) = 0;
};




