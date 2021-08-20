#pragma once
#include "Path.h"
using ListPath = std::list<Path>;
class SortPath
{
private:
	
	ListPath m_endsPaths;
	ListPath m_unfinishedPaths;
public: 
	
	ListPath& GetPaths();
	ListPath& GetEndPaths();
	void Check(Point);

};
