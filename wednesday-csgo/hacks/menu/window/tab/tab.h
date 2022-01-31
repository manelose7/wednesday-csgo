#pragma once

#include "../../../../globals/ctx/ctx.h"
#include "../../../../utils/keybinds/keybinds.h"
#include "../../../../utils/renderer/renderer.h"
#include "../../config/config.h"
#include "group/group.h"

namespace menu
{
	struct window;

	struct tab {
		tab( window* parent_window, std::string name ) : parent_window( parent_window ), name( name ){ };

		window* parent_window{ };

		std::string name{ };

		std::vector< menu::group* > groups{ };

		void draw( int& window_x, int& window_y, int& size_x, int& size_y, int current_index );
		void input( int& window_x, int& window_y, int& size_x, int& size_y, int current_index );
	};
} // namespace menu
