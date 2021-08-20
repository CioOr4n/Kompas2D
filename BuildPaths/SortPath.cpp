#include "pch.h"
#include "SortPath.h"

ListPath& SortPath::GetPaths()
{
	return m_unfinishedPaths;
}


ListPath& SortPath::GetEndPaths()
{
	return m_endsPaths;
}


void SortPath::Check(Point endDoc)
{
	ListPath::iterator it = m_unfinishedPaths.begin();
	for (auto& path : m_unfinishedPaths)
	{
		if (path.GetEndPath() == endDoc)
		{
			m_endsPaths.splice(m_endsPaths.end(), m_unfinishedPaths, it);
			break;
		}
		it++;
	}
}
