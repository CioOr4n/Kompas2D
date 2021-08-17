#include "pch.h"
#include "SortPath.h"

std::list<Path>& SortPath::GetPaths()
{
	Check();
	return m_unfinishedPaths;
}

std::list<Path>& SortPath::GetEndPaths()
{
	return m_endsPaths;
}

void SortPath::Check()
{
	std::list<Path>::iterator it = m_unfinishedPaths.begin();
	for (auto& path : m_unfinishedPaths)
	{
		if (path.IsEnd())
		{
			m_endsPaths.splice(m_endsPaths.end(), m_unfinishedPaths, it);
			break;
		}
		it++;
	}
}
