#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // класс для хранения всего пути
{

	std::list<std::unique_ptr<iFigure>> m_path; // контейнер фигур
	Point m_endPath;
	bool m_bIsEnd = false;
public:

	void Add(std::unique_ptr<iFigure> path, Point end); // добавление фигуры
	Point GetEndPath(); // получение конца пути

	void Draw(std::unique_ptr<iDrawer>& draw); // отрисовка всего пути
	bool IsEnd(); // проверка закончен ли путь
	void ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc); // парсер в xml  
};