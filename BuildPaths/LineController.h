#pragma once
#include "IController.h"

class LineController : public iController
{
private:
	bool m_bS = false, m_bE = false, m_bA = false, m_bL = false;
	TypeElem m_build;
	Point m_start, m_end;
	int m_length, m_angle;
	CBuildPathsDoc* m_pDoc;
public:
	LineController(TypeElem, CBuildPathsDoc*);
public: 
	virtual void AddPoint(Point) override;
	virtual void InputValue(TypeOfData, int) override;
	virtual void AddToPath(Path&) override;
private:
	void CalcLine();
	void EndPoints();
	Path& GetIndex();
	void Check();
	bool CheckStart();
};