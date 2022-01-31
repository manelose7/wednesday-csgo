#pragma once

#include "../../globals/ctx/ctx.h"
#include "../../utils/renderer/renderer.h"
#include "config/config.h"

namespace menu
{
	struct impl {
		bool menu_open{ };

		bool init( );

		void draw( );
	};
}; // namespace menu

inline menu::impl g_menu;
