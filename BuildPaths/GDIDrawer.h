#pragma once
#include "iDrawer.h"
#include <afxwin.h>

class GDIDrawer : public iDrawer
{
private:
	std::shared_ptr<CClientDC> m_drawer;
public: 
	GDIDrawer(std::shared_ptr<CClientDC> draw) : m_drawer(draw) {};
	virtual std::shared_ptr<CClientDC> GetScene() override;
};