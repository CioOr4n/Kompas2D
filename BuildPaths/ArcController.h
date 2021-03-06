#pragma once
#include "IController.h"
#include "CArc.h"

class ArcController : public iController
{
private:
	TypeElem m_build;
	CBuildPathsDoc* m_pDoc;
	Point m_start, m_end, m_middle, m_center;
	double m_rad;
	bool m_clock;
	bool m_bS = false, m_bR = false, m_bM = false, m_bE = false, m_bCl = false;
public:
	ArcController(TypeElem, CBuildPathsDoc*);
	virtual ~ArcController() {};
public:
	virtual void AddPoint(Point) override;
	virtual void InputValue(TypeOfData, int) override;
	virtual void AddToPath(Path&) override;
private:
	void Check(); 
	void Calc2p();
	Point Calc3p();
	void CalcClock3p();
	void EndPoints();
	Path& GetIndex();
	bool CheckStart();
};
