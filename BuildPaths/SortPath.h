#pragma once
#include "Path.h"

class SortPath
{
private:
	std::list<Path> m_endsPaths;
	std::list<Path> m_unfinishedPaths;
public: 
	std::list<Path>& GetPaths();
	std::list<Path>& GetEndPaths();
private: 
	void Check();

};
