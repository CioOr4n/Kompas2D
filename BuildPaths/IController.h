#pragma once
#define _USE_MATH_DEFINES

#include <corecrt_math_defines.h>
#include "Figures.h"
#include "BuildPathsDoc.h"

class Controller
{
public: 
	virtual void AddToPath(Path*) = 0;
	virtual void AddPoint(Point) = 0;
	virtual void SetRad(int) = 0;
	virtual void SetAngle(int) = 0;
	virtual void SetClock(bool) = 0;
	virtual void SetLength(int) = 0;
};




