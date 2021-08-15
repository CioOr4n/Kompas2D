#pragma once

#include "Figures.h"

class Path // класс для хранения всего пути
{
private:
	Point m_EndDoc;
	std::vector< std::unique_ptr<iFigure>> m_path; // контейнер фигур
	Point m_EndPath;
	bool m_bIsEnd;
public:
	Path(Point End) : m_EndDoc(End), m_bIsEnd(false) {}; // конструктор
	void Add(std::unique_ptr<iFigure> path, Point end); // добавление фигуры
	const Point GetEndPath(); // получение конца пути
	const Point GetEndDoc();
	const void Draw(std::shared_ptr <CClientDC>); // отрисовка всего пути
	const bool IsEnd(); // проверка закончен ли путь
	const void ToXML(XMLElement* path, tinyxml2::XMLDocument* doc); // парсер в xml  

};