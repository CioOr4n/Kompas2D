#pragma once
#include "IController.h"

class LineController : public Controller
{
private:
	bool m_bS = false, m_bE = false, m_bA = false, m_bL = false;
	TypeElem m_build;
	Point m_start, m_end;
	int m_length, m_angle;
	CBuildPathsDoc* m_pDoc;
public:
	LineController(TypeElem, CBuildPathsDoc*);
	virtual void SetRad(int) override {};
	virtual void SetClock(bool) override {};
	virtual void SetLength(int) override;
	virtual void SetAngle(int) override;
	virtual void AddPoint(Point) override;

private:
	void calcLine();
	virtual void AddToPath(Path*) override;
	void EndPoints();
	int GetIndex();
	void Check();
	bool CheckStart();
};