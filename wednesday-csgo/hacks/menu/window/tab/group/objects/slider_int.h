#pragma once
#include "base_object.h"

namespace menu
{
	struct group;

	struct slider_int : public base_object {
		slider_int( group* group, std::uint32_t hash, std::string name ) : parent_group( group ), option_hash( hash ), option_name( name ) { }

		group* parent_group{ };

		std::string option_name{ };
		std::uint32_t option_hash{ };

		virtual void draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void input( int& group_x, int& group_y, int& group_width, int& group_height );

		virtual void color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height );

		virtual void key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height );
	};
} // namespace menu
