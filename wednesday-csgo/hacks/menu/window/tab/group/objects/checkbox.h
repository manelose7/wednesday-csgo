#pragma once
#include "base_object.h"

namespace menu
{
	struct group;

	struct check_box : public base_object {
		check_box( group* group, std::uint32_t hash, std::string name ) : parent_group( group ), option_hash( hash ), option_name( name ) { }

		group* parent_group{ };

		std::string option_name{ };
		std::uint32_t option_hash{ };

		bool keybind{ };
		bool awaiting_keybind{ };
		std::uint32_t keybind_hash{ };

		bool color_picker{ };
		std::uint32_t color_picker_hash{ };

		void add_keybind( std::uint32_t hash );

		void add_keybind( const char* name )
		{
			add_keybind( HASH( name ) );
		}

		void add_color_picker( std::uint32_t hash );

		void add_color_picker( const char* name )
		{
			add_color_picker( HASH( name ) );
		}

		virtual void draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void input( int& group_x, int& group_y, int& group_width, int& group_height );

		virtual void color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height );

		virtual void key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height );
		virtual void key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height );
	};
} // namespace menu
