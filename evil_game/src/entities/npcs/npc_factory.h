
#pragma once

#include "../../misc/singleton.hpp"

#include "dude.hpp"
#include "slimey.hpp"

/*
Usage:

c_dude * dude = c_entity_factory::get_instance()->create_dude();
*/

class c_npc_factory : public c_singleton<c_npc_factory>
{
public:
	c_dude* create_dude()
	{
		c_dude* dude = new c_dude();

		return dude;
	}
	c_slimey* create_slimey()
	{
		c_slimey* slimey = new c_slimey();

		glm::vec3 slime_position = glm::vec3(34, 0, 31);
		slimey->initialize_monster(slime_position);


		return slimey;
	}

	void destroy_dude(c_dude* dude)
	{
		delete dude;
	}

	void destroy_slimey(c_slimey* slimey)
	{
		delete slimey;
	}
private:
};