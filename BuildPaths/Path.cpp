#include "pch.h"
#include "Path.h"

void Path::Add(std::unique_ptr<iFigure> path, Point end) // ���������� ������
{
	m_EndPath = end;
	m_path.emplace_back(std::move(path));

}

 Point Path::GetEndPath() // ��������� ����� ����
{
	return m_EndPath;
}



 void Path::Draw(std::unique_ptr<iDrawer>& draw) // ��������� ����� ����
{
	for (auto& path :m_path)
		path->DrawFigure(draw);
}

 bool Path::IsEnd() // �������� �������� �� ����
{
	return m_bIsEnd;
}

 void Path::ToXML(tinyxml2::XMLElement* path, tinyxml2::XMLDocument* doc) // ������ � xml  
{
	for (auto& paths : m_path)
	{
		paths->ToXml(path, doc);
	}

}