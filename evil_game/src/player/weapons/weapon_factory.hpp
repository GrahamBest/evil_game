
#pragma once

#include "../../misc/singleton.hpp"

#include "pistol.hpp"
/*
Usage:

c_pistol * pistol = c_weapon_factory::get_instance()->create_dude();
*/

class c_weapon_factory : public c_singleton<c_weapon_factory>
{
public:
	c_pistol* create_pistol()
	{
		c_pistol* pistol = new c_pistol();

		return pistol;
	}

	void destroy_pistol(c_pistol* pistol)
	{
		delete pistol;
	}
private:
};