#pragma once


#include <afxwin.h>
#include "Figures.h"
#define _USE_MATH_DEFINES
#include <cmath>


class iController
{

public:
	virtual void AddToPath(Path* paths) = 0;

};
class LineController : public iController
{
private:
	Point m_Start, m_End;
public:
	LineController(Point Start, Point End);
	LineController(Point Start, int nLength, double dblAngle);
	virtual void AddToPath(Path* paths) override;
};

class ArcController : public iController
{
private:
	Point m_Start, m_End, m_Center;
	bool m_clock;
private:
	Point calc3p(Point s, Point e, Point m);
public:
	ArcController(Point Start, Point End, Point Middle);
	ArcController(Point Start, Point End, double dblRadius, bool clock);
	virtual void AddToPath(Path* paths) override;


}; 
