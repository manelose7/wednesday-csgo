#pragma once
#include "../../../../config/config.h"

namespace menu
{
	struct base_object {
		std::uint32_t option_hash{ };

		virtual void draw( int& group_x, int& group_y, int& group_width, int& group_height )  = 0;
		virtual void input( int& group_x, int& group_y, int& group_width, int& group_height ) = 0;

		virtual void color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height )  = 0;
		virtual void color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height ) = 0;

		virtual void key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height )  = 0;
		virtual void key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height ) = 0;
	};
} // namespace menu
