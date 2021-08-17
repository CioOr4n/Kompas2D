#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // класс для хранения всего пути
{
private:
	Point m_EndDoc;
	std::list<std::unique_ptr<iFigure>> m_path; // контейнер фигур
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End), m_bIsEnd(false) {}; // конструктор
	void Add(std::unique_ptr<iFigure> path, Point end); // добавление фигуры
	const Point GetEndPath(); // получение конца пути

	const void Draw(std::unique_ptr<iDrawer>& draw); // отрисовка всего пути
	const bool IsEnd(); // проверка закончен ли путь
	const void ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc); // парсер в xml  
};