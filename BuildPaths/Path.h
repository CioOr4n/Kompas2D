#pragma once

#include "Figures.h"
#include <list>
#include "iDrawer.h"

class Path // класс для хранения всего пути
{
private:
	std::list<std::unique_ptr<iFigure>> m_path; // контейнер фигур
	Point m_endPath;
public:
	void Add(std::unique_ptr<iFigure>, Point); // добавление фигуры
	Point GetEndPath(); // получение конца пути
	void Draw(iDrawer &); // отрисовка всего пути
	void ToXML(tinyxml2::XMLElement*, tinyxml2::XMLDocument*); // парсер в xml  
};