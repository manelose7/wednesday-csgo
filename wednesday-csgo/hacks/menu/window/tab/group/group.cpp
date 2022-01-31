#include "group.h"

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
		g_render.render_rectangle( group_position_x, group_position_y, group_width, font_size.y + 1, { 43, 43, 43 } );

		g_render.render_text( group_position_x + group_with_half, group_position_y + static_cast< int >( font_size.y ) / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( name.c_str( ) ),
		                      menu_font, color( 255, 255, 255 ) );

		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		g_render.render_filled_rectangle( group_position_x, group_position_y, group_width, group_height, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x, group_position_y, group_width, group_height, { 43, 43, 43 } );

		for ( auto& object : objects )
			object->draw( group_position_x, group_position_y, group_width, group_height );
	} else {
		int right_adjustment = ( ( size_x - 6 ) / 2 ) + 2;

		int group_width     = ( size_x - 11 ) / 2;
		int group_height    = extended ? ( size_y - 50 ) : ( ( size_y - 52 ) / 2 );
		int group_with_half = group_width / 2;

		int group_position_x = ( window_x + 3 );
		int group_position_y = ( window_y + 46 ) + ( group_height * current_index ) + ( current_index == 0 ? 0 : 2 );

		auto font_size = g_render.render_text_size( _( name.c_str( ) ), menu_font );

		g_render.render_filled_rectangle( group_position_x + right_adjustment, group_position_y, group_width, font_size.y + 1, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x + right_adjustment, group_position_y, group_width, font_size.y + 1, { 43, 43, 43 } );

		g_render.render_text( group_position_x + right_adjustment + group_with_half, group_position_y + static_cast< int >( font_size.y ) / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( name.c_str( ) ),
		                      menu_font, color( 255, 255, 255 ) );

		group_position_x += right_adjustment;
		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		g_render.render_filled_rectangle( group_position_x, group_position_y, group_width, group_height, { 20, 20, 20 } );
		g_render.render_rectangle( group_position_x, group_position_y, group_width, group_height, { 43, 43, 43 } );

		for ( auto& object : objects )
			object->draw( group_position_x, group_position_y, group_width, group_height );
	}
}

void menu::group::input( int& window_x, int& window_y, int& size_x, int& size_y, int current_index )
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

		group_position_y += font_size.y + 3;
		group_height -= font_size.y + 3;

		for ( auto& object : objects )
			object->input( group_position_x, group_position_y, group_width, group_height );
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

		for ( auto& object : objects )
			object->input( group_position_x, group_position_y, group_width, group_height );
	}
}
