#include "checkbox.h"
#include "../../../window.h"
#include "../group.h"

void menu::check_box::draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	// ur mic is shit btw blanket

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	auto checkbox_x = group_x + font_size.y / 2 + 1;
	auto checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< bool >( option_hash );

	if ( option )
		g_render.render_filled_rectangle( checkbox_x, checkbox_y, 8, 8, menu_color );

	g_render.render_rectangle( checkbox_x, checkbox_y, 8, 8, { 43, 43, 43 } );

	g_render.render_text( checkbox_x + font_size.y / 2 + 8, checkbox_y + 4, font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE,
	                      _( option_name.c_str( ) ), menu_font, color( 255, 255, 255 ) );

	group_y += ( checkbox_y + 4 ) - group_y;
}

void menu::check_box::input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int checkbox_x = group_x + font_size.y / 2 + 1;
	int checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< bool >( option_hash );

	if ( menu::window::inside_position( { mouse_x, mouse_y }, { checkbox_x, checkbox_y }, { 8, 8 } ) ) {
		parent_group->parent_tab->parent_window->allowed_to_drag = false;

		if ( g_input.key_state< input::KEY_RELEASED >( VK_LBUTTON ) )
			option = !option;
	}

	group_y += ( checkbox_y + 4 ) - group_y;
}
