#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <afxwin.h>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;
enum class TypeElem {line2p, linela, arc3p,arc2p}; // перечисления для выбора фигур
enum class Type { line, Arc }; // перечисление для вид фигур
struct Point // координаты точек в структуре
{
	int m_x, m_y;
};

class iFigure // интерфейс
{
public:
	virtual void DrawFigure(CClientDC* canvas) = 0; // отрисовка фигуры
	virtual Type FigureType() = 0; // тип фигуры
};

class CArc : public iFigure // класс Arc
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

class Path // класс для хранения всего пути
{
public:
	std::vector<iFigure*> m_path; // контейнер фигур
	Point m_EndDoc;
private:
	
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End) {}; // конструктор
	void Add(iFigure* elem, Point end) // добавление фигуры
	{
		m_EndPath = end;
		m_path.push_back(elem);
		if ((m_EndPath.m_x == m_EndDoc.m_x) & (m_EndPath.m_y == m_EndDoc.m_y))
			m_bIsEnd = !m_bIsEnd;
	}
	Point GetEnd() // получение конца пути
	{
		return m_EndPath;
	}
	void Draw(CClientDC* canvas) // отрисовка всего пути
	{
		for (int i = 0; i < m_path.size(); i++)
			m_path[i]->DrawFigure(canvas);
	}
	bool IsEnd() // проверка закончен ли путь
	{
		return m_bIsEnd;
	}
	void ToXML(XMLElement* path, tinyxml2::XMLDocument* doc) // парсер в xml  
	{
		for (int i = 0; i < m_path.size(); i++)
		{
			switch (m_path[i]->FigureType()) // получение типа фигуры
			{
			case Type::line:
			{
				// приводим к типу line
				LineSegment* line = static_cast<LineSegment*>(m_path[i]);
				//создаем элемента линии
				XMLElement* Line = doc->NewElement("LineSegment");
				path->InsertEndChild(Line);
				//Создаем стартовую точку
				XMLElement* StartPoint = doc->NewElement("StartPoint");
				Line->InsertEndChild(StartPoint);
				// создаем точку x
				XMLElement* xs = doc->NewElement("x");
				xs->SetText(line->m_Start.m_x);
				StartPoint->InsertEndChild(xs);
				// создаем точку y
				XMLElement* ys = doc->NewElement("y");
				ys->SetText(line->m_Start.m_y);
				StartPoint->InsertEndChild(ys);
				//Создаем конечную точку
				XMLElement* FinishPoint = doc->NewElement("FinishPoint");
				Line->InsertEndChild(FinishPoint);
				// создаем точку x
				XMLElement* xf = doc->NewElement("x");
				xf->SetText(line->m_End.m_x);
				FinishPoint->InsertEndChild(xf);
				// создаем точку y
				XMLElement* yf = doc->NewElement("y");
				yf->SetText(line->m_End.m_y);
				FinishPoint->InsertEndChild(yf);
				
			}
			break;
			case Type::Arc:
			{
				// приводим к типу Carc
				CArc* arc = static_cast<CArc*>(m_path[i]);
				//создаем элемента arc
				XMLElement* ArcSegment = doc->NewElement("Arc");
				//добавляем аттрибут направление дуги
				ArcSegment->SetAttribute("Clock", arc->m_bClock);
				path->InsertEndChild(ArcSegment);
				//Создаем стартовую точку
				XMLElement* StartPoint = doc->NewElement("StartPoint");
				ArcSegment->InsertEndChild(StartPoint);
				// создаем точку x
				XMLElement* xs = doc->NewElement("x");
				xs->SetText(arc->m_Start.m_x);
				StartPoint->InsertEndChild(xs);
				// создаем точку y
				XMLElement* ys = doc->NewElement("y");
				ys->SetText(arc->m_Start.m_y);
				StartPoint->InsertEndChild(ys);
				//Создаем Центр дуги
				XMLElement* CenterPoint = doc->NewElement("CenterPoint");
				ArcSegment->InsertEndChild(CenterPoint);
				// создаем точку x
				XMLElement* xc = doc->NewElement("x");
				xc->SetText(arc->m_Center.m_x);
				CenterPoint->InsertEndChild(xc);
				// создаем точку y
				XMLElement* yc = doc->NewElement("y");
				yc->SetText(arc->m_Center.m_y);
				CenterPoint->InsertEndChild(yc);
				//Создаем конечную точку
				XMLElement* FinishPoint = doc->NewElement("FinishPoint");
				ArcSegment->InsertEndChild(FinishPoint);
				// создаем точку x
				XMLElement* xf = doc->NewElement("x");
				xf->SetText(arc->m_End.m_x);
				FinishPoint->InsertEndChild(xf);
				// создаем точку y
				XMLElement* yf = doc->NewElement("y");
				yf->SetText(arc->m_End.m_y);
				FinishPoint->InsertEndChild(yf);
			}
			break;
			}
			
		}
	}

};



