#pragma once

#include "../../../globals/ctx/ctx.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../../utils/renderer/renderer.h"
#include "../config/config.h"
#include "tab/tab.h"

namespace menu
{
	struct window {
		bool dragging{ };
		std::uint32_t dragged_object{ };

		bool resizing{ };
		bool allowed_to_drag{ };

		std::uint32_t selected_tab{ };
		std::vector< menu::tab* > tabs{ };

		static bool inside_position( math::vec2< int > mouse_position, math::vec2< int > window_position, math::vec2< int > window_size );

		void draw( int& window_x, int& window_y, int& size_x, int& size_y );
		void input( int& window_x, int& window_y, int& size_x, int& size_y );
	};
} // namespace menu
