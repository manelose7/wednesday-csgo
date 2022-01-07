#pragma once
#include "../../../utils/math/types/vector.h"
#include <stack>
#include <string_view>
#include <vector>

#define UNFOCUSED 0

namespace gui
{
	// window
	struct window_ctx {
		// TODO: on position, calculate middle of screen to spawn menu in(menu width / 2 - screen width / 2)
		math::vec2< int > position = { 250, 250 };
		math::vec2< int > size     = { 537, 621 };

		// cursors / focus
		std::stack< math::vec2< int > > cursor_pos_stack;
		std::size_t focused_id;

		// tabs
		std::vector< std::string_view > tabs;
		int active_tab = 0;

		struct {
			bool open     = true;
			bool dragging = false;
			bool resizing = false;
			float alpha   = 0.f;
		} main;
	};
} // namespace gui

inline gui::window_ctx g_gui;
