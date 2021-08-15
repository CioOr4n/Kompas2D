#pragma once
#include <memory>
class iDrawer
{
public:
	virtual std::shared_ptr<CClientDC> GetScene() = 0;
};