#pragma once
#include "IController.h"
#include "CArc.h"
class ArcController : public Controller
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
	virtual void AddPoint(Point) override;

	virtual void SetRad(int) override;
	virtual void SetClock(bool) override;
	virtual void SetLength(int) override {};
	virtual void SetAngle(int) override {};
private:
	virtual void AddToPath(Path*) override;
	void Check();
	void calc2p();
	Point calc3p();
	void calcClock3p();
	void EndPoints();
	int GetIndex();
	bool CheckStart();
};
