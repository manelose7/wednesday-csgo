#include "tab.h"
#include "../window.h"

void menu::tab::draw( int& window_x, int& window_y, int& size_x, int& size_y, int current_index )
{
	auto current_x  = ( ( size_x - 7 ) / parent_window->tabs.size( ) ) * current_index;
	auto adjusted_x = ( ( size_x - 7 ) / parent_window->tabs.size( ) ) * ( current_index + 1 );
	auto centered_x = ( ( window_x + adjusted_x ) - ( window_x + current_x ) ) / 2;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	g_render.render_text( window_x + current_x + centered_x, window_y + 28 + g_render.render_text_size( name.c_str( ), menu_font ).y / 2,
	                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, name.c_str( ), menu_font,
	                      parent_window->selected_tab == HASH( name.c_str( ) ) ? menu_color : color( 255, 255, 255 ) );

	int _current_index[ 2 ]{ };

	if ( parent_window->selected_tab != HASH( name.c_str( ) ) )
		return;

	for ( auto& group : groups )
		group->draw( window_x, window_y, size_x, size_y,
		             group->position & static_cast< int >( menu::group_position::GROUP_LEFT ) ? _current_index[ 0 ]++ : _current_index[ 1 ]++ );
}

void menu::tab::input( int& window_x, int& window_y, int& size_x, int& size_y, int current_index )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	int current_x  = ( ( size_x - 7 ) / parent_window->tabs.size( ) ) * current_index;
	int adjusted_x = ( ( size_x - 7 ) / parent_window->tabs.size( ) ) * ( current_index + 1 );
	int centered_x = ( ( window_x + adjusted_x ) - ( window_x + current_x ) ) / 2;

	math::vec2 window_inset = { window_x + 3, window_y + 24 };

	if ( menu::window::inside_position( { mouse_x, mouse_y }, { window_x + current_x, window_y + 26 }, { adjusted_x - current_x, 20 } ) &&
	     !parent_window->dragging ) {
		parent_window->allowed_to_drag = false;

		if ( g_input.key_state< input::KEY_RELEASED >( VK_LBUTTON ) ) {
			parent_window->selected_tab = HASH( name.c_str( ) );
		}
	}

	int _current_index[ 2 ]{ };

	if ( parent_window->selected_tab != HASH( name.c_str( ) ) )
		return;

	for ( auto& group : groups )
		group->input( window_x, window_y, size_x, size_y,
		              group->position & static_cast< int >( menu::group_position::GROUP_LEFT ) ? _current_index[ 0 ]++ : _current_index[ 1 ]++ );
}
