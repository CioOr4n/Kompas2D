#include "pch.h"
#include "Path.h"

void Path::Add(std::unique_ptr<iFigure> path, Point end) // добавление фигуры
{
	m_endPath = end;
	m_path.emplace_back(std::move(path));
}


Point Path::GetEndPath() // получение конца пути
{
	return m_endPath;
}



void Path::Draw(iDrawer& draw) // отрисовка всего пути
{
	for (auto& path :m_path)
		path->DrawFigure(draw);
}


void Path::ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) // парсер в xml  
{
	for (auto& paths : m_path)
	{
		paths->ToXml(path, doc);
	}

}