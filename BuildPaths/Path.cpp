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

const Point Path::GetEndDoc()
{
	return m_EndDoc;
}

const void Path::Draw(CClientDC* canvas) // отрисовка всего пути
{
	for (int i = 0; i < m_path.size(); i++)
		m_path[i]->DrawFigure(canvas);
}

const bool Path::IsEnd() // проверка закончен ли путь
{
	return m_bIsEnd;
}

const void Path::ToXML(XMLElement* path, tinyxml2::XMLDocument* doc) // парсер в xml  
{
	for (int i = 0; i < m_path.size(); i++)
	{
		m_path[i]->ToXml(path, doc);
	}

}