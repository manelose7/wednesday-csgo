#pragma once
#include "../../game/sdk/classes/c_base_player.h"
#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/i_client_entity.h"
#include "../../globals/interfaces/interfaces.h"

#include <deque>

namespace entity_list
{
	struct player_info {
	public:
		std::string m_name;

		math::vec3 m_mins{ };
		math::vec3 m_maxs{ };

		math::matrix_3x4 m_rgfl{ };

		int m_index{ };

		bool m_valid{ };

		sdk::c_base_combat_weapon* m_weapon{ };
	};

	struct impl {
		std::array< player_info, 65 > players;

		void update( );
	};
} // namespace entity_list

inline entity_list::impl g_entity_list;
