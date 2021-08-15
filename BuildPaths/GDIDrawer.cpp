#include "pch.h"
#include "GDIDrawer.h"

std::shared_ptr<CClientDC> GDIDrawer::GetScene()
{
    return m_drawer;
}
