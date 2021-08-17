#include "pch.h"
#include "Path.h"

void Path::Add(std::unique_ptr<iFigure> path, Point end) // добавление фигуры
{
	m_EndPath = end;
	m_path.emplace_back(std::move(path));
	if ((abs(m_EndPath.m_x - m_EndDoc.m_x) < 10) & (abs(m_EndPath.m_y - m_EndDoc.m_y) < 10))
		m_bIsEnd = !m_bIsEnd;
}

const Point Path::GetEndPath() // получение конца пути
{
	return m_EndPath;
}



const void Path::Draw(std::unique_ptr<iDrawer>& draw) // отрисовка всего пути
{
	for (auto& path :m_path)
		path->DrawFigure(draw);
}

const bool Path::IsEnd() // проверка закончен ли путь
{
	return m_bIsEnd;
}

const void Path::ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) // парсер в xml  
{
	for (auto& paths : m_path)
	{
		paths->ToXml(path, doc);
	}

}