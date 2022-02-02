#include "group.h"
#include "../../window.h"

void menu::group::draw( int& window_x, int& window_y, int& size_x, int& size_y, int current_index )
{
	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	if ( position & static_cast< int >( group_position::GROUP_LEFT ) ) {
		int group_width     = ( size_x - 6 ) / 2;
		int group_height    = extended ? ( size_y - 50 ) : ( ( size_y - 52 ) / 2 );
		int group_with_half = group_width / 2;

		int group_position_x = ( window_x + 3 );
		int group_position_y = ( window_y + 46 ) + ( group_height * current_index ) + ( current_index == 0 ? 0 : 2 );

		auto font_size = g_render.render_text_size( _( name.c_str( ) ), menu_font );

		g_render.render_filled_rectangle( group_position_x, group_position_y, group_width, font_size.y + 1, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x, group_position_y, group_width, font_size.y + 1, { 30, 30, 30 } );

		g_render.render_text( group_position_x + group_with_half, group_position_y + static_cast< int >( font_size.y ) / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( name.c_str( ) ),
		                      menu_font, color( 255, 255, 255 ) );

		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		g_render.render_filled_rectangle( group_position_x, group_position_y, group_width, group_height, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x, group_position_y, group_width, group_height, { 30, 30, 30 } );

		auto old_viewport = g_render.get_viewport( );

		g_render.set_viewport( { group_position_x, group_position_y }, { group_width, group_height } );

		group_position_y -= scroll_amount;

		for ( auto& object : objects )
			object->draw( group_position_x, group_position_y, group_width, group_height );

		g_render.set_viewport( old_viewport );
	} else {
		int right_adjustment = ( ( size_x - 6 ) / 2 ) + 2;

		int group_width     = ( size_x - 11 ) / 2;
		int group_height    = extended ? ( size_y - 50 ) : ( ( size_y - 52 ) / 2 );
		int group_with_half = group_width / 2;

		int group_position_x = ( window_x + 3 );
		int group_position_y = ( window_y + 46 ) + ( group_height * current_index ) + ( current_index == 0 ? 0 : 2 );

		auto font_size = g_render.render_text_size( _( name.c_str( ) ), menu_font );

		g_render.render_filled_rectangle( group_position_x + right_adjustment, group_position_y, group_width, font_size.y + 1, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x + right_adjustment, group_position_y, group_width, font_size.y + 1, { 30, 30, 30 } );

		g_render.render_text( group_position_x + right_adjustment + group_with_half, group_position_y + static_cast< int >( font_size.y ) / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( name.c_str( ) ),
		                      menu_font, color( 255, 255, 255 ) );

		group_position_x += right_adjustment;
		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		g_render.render_filled_rectangle( group_position_x, group_position_y, group_width, group_height, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x, group_position_y, group_width, group_height, { 30, 30, 30 } );

		auto old_viewport = g_render.get_viewport( );

		g_render.set_viewport( { group_position_x, group_position_y }, { group_width, group_height } );

		group_position_y -= scroll_amount;

		for ( auto& object : objects )
			object->draw( group_position_x, group_position_y, group_width, group_height );

		g_render.set_viewport( old_viewport );
	}
}

void menu::group::input( int& window_x, int& window_y, int& size_x, int& size_y, int current_index )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	if ( position & static_cast< int >( group_position::GROUP_LEFT ) ) {
		int group_width     = ( size_x - 6 ) / 2;
		int group_height    = extended ? ( size_y - 50 ) : ( ( size_y - 52 ) / 2 );
		int group_with_half = group_width / 2;

		int group_position_x = ( window_x + 3 );
		int group_position_y = ( window_y + 46 ) + ( group_height * current_index ) + ( current_index == 0 ? 0 : 2 );

		auto font_size = g_render.render_text_size( _( name.c_str( ) ), menu_font );

		if ( menu::window::inside_position( { mouse_x, mouse_y }, { group_position_x, group_position_y }, { group_width, group_height } ) &&
		     needed_scroll_amount > 0 ) {
			scroll_amount = std::clamp( scroll_amount + g_input.mouse.scroll_amt, 0, needed_scroll_amount );

			g_input.mouse.scroll_amt = 0;
		}

		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		auto old_viewport = g_render.get_viewport( );

		g_render.set_viewport( { group_position_x, group_position_y + 1 }, { group_width, group_height } );

		group_position_y -= scroll_amount;

		for ( auto& object : objects )
			object->input( group_position_x, group_position_y, group_width, group_height );

		g_render.set_viewport( old_viewport );
	} else {
		int right_adjustment = ( ( size_x - 6 ) / 2 ) + 2;

		int group_width     = ( size_x - 11 ) / 2;
		int group_height    = extended ? ( size_y - 50 ) : ( ( size_y - 52 ) / 2 );
		int group_with_half = group_width / 2;

		int group_position_x = ( window_x + 3 );
		int group_position_y = ( window_y + 46 ) + ( group_height * current_index ) + ( current_index == 0 ? 0 : 2 );

		auto font_size = g_render.render_text_size( _( name.c_str( ) ), menu_font );

		group_position_x += right_adjustment;
		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		auto old_viewport = g_render.get_viewport( );

		g_render.set_viewport( { group_position_x, group_position_y + 1 }, { group_width, group_height } );

		group_position_y -= scroll_amount;

		for ( auto& object : objects )
			object->input( group_position_x, group_position_y, group_width, group_height );

		g_render.set_viewport( old_viewport );
	}
}
