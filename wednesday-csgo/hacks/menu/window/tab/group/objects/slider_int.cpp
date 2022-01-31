#include "slider_int.h"
#include "../../../window.h"
#include "../group.h"

void menu::slider_int::draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	// ur mic is shit btw blanket

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	auto slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	auto slider_border_height = slider_y + 12;

	int option_min{ };
	int option_max{ };

	auto& option = g_config.find< int >( option_hash, option_min, option_max );

	g_render.render_text( slider_x + font_size.y / 2, slider_y + 4, AL_VERTICAL_CENTER, FLAG_NONE, _( option_name.c_str( ) ), menu_font,
	                      color( 255, 255, 255 ) );

	g_render.render_text( slider_border_width, slider_y + 5, AL_HORIZONTAL_LEFT | AL_VERTICAL_CENTER, FLAG_NONE,
	                      _( std::to_string( option ).c_str( ) ), menu_font, color( 255, 255, 255 ) );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width = slider_distance * slider_fraction;

	g_render.render_filled_rectangle( slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2, slider_width, slider_border_height - slider_y,
	                                  menu_color );

	g_render.render_rectangle( slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2, slider_border_width - slider_x - 7,
	                           slider_border_height - slider_y, { 43, 43, 43 } );

	group_y += slider_border_height - slider_y + 20;
}

void menu::slider_int::input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	auto slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	auto slider_border_height = slider_y + 12;

	int option_min{ };
	int option_max{ };

	auto& option = g_config.find< int >( option_hash, option_min, option_max );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width = slider_distance * slider_fraction;

	int weird_inset = 11;

	if ( menu::window::inside_position(
			 { mouse_x, mouse_y },
			 { slider_x + static_cast< int >( font_size.y / 2 ) - 8, slider_y + static_cast< int >( font_size.y / 2 ) + 2 + weird_inset - 8 },
			 { static_cast< int >( slider_border_width ) - slider_x - 7 + 12, ( slider_border_height - slider_y ) } ) ) {
		parent_group->parent_tab->parent_window->allowed_to_drag = false;

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) ) {
			auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
			auto slider_fraction = ( mouse_x - ( slider_x + font_size.y / 2 ) );

			float slider_width = slider_fraction / slider_distance;

			option =
				static_cast< int >( std::clamp( option_max * slider_width, static_cast< float >( option_min ), static_cast< float >( option_max ) ) );
		}
	}

		group_y += slider_border_height - slider_y + 20;

}
