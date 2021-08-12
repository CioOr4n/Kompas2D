#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <afxwin.h>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;
enum class TypeElem {line2p, linela, arc3p,arc2p};
enum class Type { line, Arc };
struct Point
{
	int m_x, m_y;
};

class iFigure
{
public:
	virtual void DrawFigure(CClientDC* canvas) = 0;
	virtual Type FigureType() = 0;
};

class CArc : public iFigure
{
public:
	Point m_Start, m_End, m_Center;
	bool m_bClock;
public:
	virtual void DrawFigure(CClientDC* canvas) override;
	virtual Type FigureType() override;
	CArc(Point Start, Point End, Point Center,bool clock);

};

class LineSegment : public iFigure
{
public:
	Point m_Start, m_End;
public:
	virtual void DrawFigure(CClientDC* canvas) override;
	virtual Type FigureType() override;
	LineSegment(Point Start, Point End);
};

class Path
{
public:
	std::vector<iFigure*> m_path;
	Point m_EndDoc;
private:
	
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End) {};
	void Add(iFigure* elem, Point end)
	{
		m_EndPath = end;
		m_path.push_back(elem);
		if ((m_EndPath.m_x == m_EndDoc.m_x) & (m_EndPath.m_y == m_EndDoc.m_y))
			m_bIsEnd = !m_bIsEnd;
	}
	Point GetEnd()
	{
		return m_EndPath;
	}
	void Draw(CClientDC* canvas)
	{
		for (int i = 0; i < m_path.size(); i++)
			m_path[i]->DrawFigure(canvas);
	}
	bool IsEnd()
	{
		return m_bIsEnd;
	}
	void ToXML(XMLElement* path, tinyxml2::XMLDocument* doc)
	{
		for (int i = 0; i < m_path.size(); i++)
		{
			switch (m_path[i]->FigureType())
			{
			case Type::line:
			{
				LineSegment* line = static_cast<LineSegment*>(m_path[i]);
				XMLElement* Line = doc->NewElement("LineSegment");
				path->InsertEndChild(Line);
				XMLElement* StartPoint = doc->NewElement("StartPoint");
				Line->InsertEndChild(StartPoint);
				XMLElement* xs = doc->NewElement("x");
				xs->SetText(line->m_Start.m_x);
				StartPoint->InsertEndChild(xs);
				XMLElement* ys = doc->NewElement("y");
				ys->SetText(line->m_Start.m_y);
				StartPoint->InsertEndChild(ys);
				XMLElement* FinishPoint = doc->NewElement("FinishPoint");
				Line->InsertEndChild(FinishPoint);
				XMLElement* xf = doc->NewElement("x");
				xf->SetText(line->m_End.m_x);
				FinishPoint->InsertEndChild(xf);
				XMLElement* yf = doc->NewElement("y");
				yf->SetText(line->m_End.m_y);
				FinishPoint->InsertEndChild(yf);
				
			}
			break;
			case Type::Arc:
			{
				CArc* arc = static_cast<CArc*>(m_path[i]);
				XMLElement* ArcSegment = doc->NewElement("Arc");
				ArcSegment->SetAttribute("Clock", arc->m_bClock);
				path->InsertEndChild(ArcSegment);
				XMLElement* StartPoint = doc->NewElement("StartPoint");
				ArcSegment->InsertEndChild(StartPoint);
				XMLElement* xs = doc->NewElement("x");
				xs->SetText(arc->m_Start.m_x);
				StartPoint->InsertEndChild(xs);
				XMLElement* ys = doc->NewElement("y");
				ys->SetText(arc->m_Start.m_y);
				StartPoint->InsertEndChild(ys);
				XMLElement* CenterPoint = doc->NewElement("CenterPoint");
				ArcSegment->InsertEndChild(CenterPoint);
				XMLElement* xc = doc->NewElement("x");
				xc->SetText(arc->m_Center.m_x);
				CenterPoint->InsertEndChild(xc);
				XMLElement* yc = doc->NewElement("y");
				yc->SetText(arc->m_Center.m_y);
				CenterPoint->InsertEndChild(yc);
				XMLElement* FinishPoint = doc->NewElement("FinishPoint");
				ArcSegment->InsertEndChild(FinishPoint);
				XMLElement* xf = doc->NewElement("x");
				xf->SetText(arc->m_End.m_x);
				FinishPoint->InsertEndChild(xf);
				XMLElement* yf = doc->NewElement("y");
				yf->SetText(arc->m_End.m_y);
				FinishPoint->InsertEndChild(yf);
			}
			break;
			}
			
		}
	}

};



