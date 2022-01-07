#pragma once

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../globals/includes/includes.h"

namespace aimbot
{
	struct impl {
	private:
		sdk::c_cs_player* find_closest( );

	public:
		void run( );
	};
} // namespace aimbot

inline aimbot::impl g_aimbot;
