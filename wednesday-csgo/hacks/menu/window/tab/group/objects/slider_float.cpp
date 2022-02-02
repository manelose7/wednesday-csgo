#include "slider_float.h"
#include "../../../window.h"
#include "../group.h"

void menu::slider_float::draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	// ur mic is shit btw blanket

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	auto slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	auto slider_border_height = slider_y + 12;

	float option_min{ };
	float option_max{ };

	auto& option = g_config.find< float >( option_hash, option_min, option_max );

	g_render.render_text( slider_x + font_size.y / 2, slider_y + 4, AL_VERTICAL_CENTER, FLAG_NONE, _( option_name.c_str( ) ), menu_font,
	                      color( 255, 255, 255 ) );

	g_render.render_text( slider_border_width, slider_y + 5, AL_HORIZONTAL_LEFT | AL_VERTICAL_CENTER, FLAG_NONE,
	                      _( fmt::format( "{0:0.1f}", option ).c_str( ) ), menu_font, color( 255, 255, 255 ) );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width = slider_distance * slider_fraction;

	g_render.render_filled_rectangle( slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2, slider_width, slider_border_height - slider_y,
	                                  menu_color );

	g_render.render_rectangle( slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2, slider_border_width - slider_x - 7,
	                           slider_border_height - slider_y, { 43, 43, 43 } );

	group_y += slider_border_height - slider_y + 20;

	auto viewport = g_render.get_viewport( );

	int distance = group_y - static_cast< int >( viewport.Y );

	parent_group->needed_scroll_amount = distance;
}

void menu::slider_float::input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	int slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	int slider_border_height = slider_y + 12;

	float option_min{ };
	float option_max{ };

	auto& option = g_config.find< float >( option_hash, option_min, option_max );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width   = slider_distance * slider_fraction;
	auto& parent_window = parent_group->parent_tab->parent_window;

	if ( menu::window::inside_position( { mouse_x, mouse_y },
	                                    { slider_x + static_cast< int >( font_size.y ) / 2, slider_y + static_cast< int >( font_size.y ) / 2 + 2 },
	                                    { slider_border_width - slider_x - 7, slider_border_height - slider_y } ) ||
	     ( parent_window->dragging && parent_window->dragged_object == option_hash ) ) {
		parent_group->parent_tab->parent_window->allowed_to_drag = false;

		auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
		auto slider_fraction = ( mouse_x - ( slider_x + font_size.y / 2 ) );

		float slider_width = slider_fraction / slider_distance;

		auto viewport = g_render.get_viewport( );

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) ) {
			int distance = ( slider_y + static_cast< int >( font_size.y ) / 2 + 2 ) - static_cast< int >( viewport.Y );

			if ( distance < group_height && distance > 0 ) {
				parent_window->dragging       = true;
				parent_window->dragged_object = option_hash;

				option = static_cast< float >(
					std::clamp( option_max * slider_width, static_cast< float >( option_min ), static_cast< float >( option_max ) ) );
			}
		} else {
			parent_group->parent_tab->parent_window->dragging       = false;
			parent_group->parent_tab->parent_window->dragged_object = { };
		}
	}

	group_y += slider_border_height - slider_y + 20;
}

void menu::slider_float::color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_float::color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_float::key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_float::key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height ) { }
