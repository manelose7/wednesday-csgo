#include "checkbox.h"
#include "../../../window.h"
#include "../group.h"

void menu::check_box::add_keybind( std::uint32_t hash )
{
	keybind      = true;
	keybind_hash = hash;

	auto& keybind_char = g_config.find< std::uint8_t >( keybind_hash );
	auto& option       = g_config.find< bool >( option_hash );

	g_input.poll_keybind(
		[ & ]( std::uint8_t key, bool pressed ) {
			auto& keybind_option = g_config.find< std::uint8_t >( keybind_hash );

			if ( pressed && keybind_option == key )
				option = !option;

			if ( awaiting_keybind ) {
				awaiting_keybind = false;

				keybind_option = key;
			}
		},
		[ & ]( bool pressed ) {
			if ( !awaiting_keybind )
				return;

			auto& keybind_option = g_config.find< std::uint8_t >( keybind_hash );

			awaiting_keybind = false;
			keybind_option   = { };
		} );
}

void menu::check_box::add_color_picker( std::uint32_t hash )
{
	color_picker      = true;
	color_picker_hash = hash;
}

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

	if ( keybind )
		key_bind_draw( group_x, group_y, group_width, group_height );

	if ( color_picker )
		color_picker_draw( group_x, group_y, group_width, group_height );

	group_y += ( checkbox_y + 4 ) - group_y;

	auto viewport = g_render.get_viewport( );

	int distance = ( group_y + group_height ) - ( static_cast< int >( viewport.Y ) + group_height );

	parent_group->needed_scroll_amount = distance;
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

	if ( keybind )
		key_bind_input( group_x, group_y, group_width, group_height );

	if ( color_picker )
		color_picker_input( group_x, group_y, group_width, group_height );

	group_y += ( checkbox_y + 4 ) - group_y;

	if ( menu::window::inside_position( { mouse_x, mouse_y }, { checkbox_x, checkbox_y }, { 8, 8 } ) ) {
		parent_group->parent_tab->parent_window->allowed_to_drag = false;

		if ( g_input.key_state< input::KEY_RELEASED >( VK_LBUTTON ) ) {
			auto viewport = g_render.get_viewport( );

			int distance = ( group_y + group_height ) - ( static_cast< int >( viewport.Y ) + group_height );

			if ( distance < group_height && distance > 0 )
				option = !option;
		}
	}
}

void menu::check_box::color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	auto checkbox_x = group_x + font_size.y / 2 + 1;
	auto checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< color >( color_picker_hash );

	checkbox_x = ( group_x + group_width - font_size.y / 2 - 20 ) - 1;

	g_render.render_filled_rectangle( checkbox_x, checkbox_y, 20, 8, option );
	g_render.render_rectangle( checkbox_x, checkbox_y, 20, 8, { 42, 42, 42 } );
}

void menu::check_box::color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto font_size = g_render.render_text_size( _( option_name.c_str( ) ), menu_font );

	int checkbox_x = group_x + font_size.y / 2 + 1;
	int checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< color >( color_picker_hash );

	checkbox_x = ( group_x + group_width - font_size.y / 2 - 20 ) - 1;

	if ( menu::window::inside_position( { mouse_x, mouse_y }, { checkbox_x, checkbox_y }, { 20, 8 } ) ) {
		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) ) {
			parent_group->parent_tab->parent_window->selected_color_picker = color_picker_hash;
			parent_group->parent_tab->parent_window->color_picker_x        = mouse_x;
			parent_group->parent_tab->parent_window->color_picker_y        = mouse_y;
		}
	}
}

void menu::check_box::key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto keybind_char = g_config.find< std::uint8_t >( keybind_hash );

	auto font_size = g_render.render_text_size(
		!keybind_char || awaiting_keybind ? _( "[-]" ) : fmt::format( _( "[{}]" ), g_input.key_to_char( keybind_char ) ).c_str( ), menu_font );

	auto checkbox_x = group_x + font_size.y / 2 + 1;
	auto checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< bool >( option_hash );

	checkbox_x = ( group_x + group_width - font_size.y / 2 ) - 1;

	g_render.render_text( checkbox_x, checkbox_y + 4, AL_VERTICAL_CENTER | AL_HORIZONTAL_LEFT, font_flags::FLAG_NONE,
	                      !keybind_char || awaiting_keybind ? _( "[-]" ) : fmt::format( _( "[{}]" ), g_input.key_to_char( keybind_char ) ).c_str( ),
	                      menu_font, { 43, 43, 43 } );
}

void menu::check_box::key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	auto keybind_char = g_config.find< std::uint8_t >( keybind_hash );

	auto font_size = g_render.render_text_size(
		!keybind_char || awaiting_keybind ? _( "[-]" ) : fmt::format( _( "[{}]" ), g_input.key_to_char( keybind_char ) ).c_str( ), menu_font );

	int checkbox_x = group_x + font_size.y / 2 + 1;
	int checkbox_y = group_y + font_size.y / 2 + 1;

	auto& option = g_config.find< bool >( option_hash );

	checkbox_x = ( group_x + group_width - font_size.y / 2 ) - 1;

	if ( menu::window::inside_position( { mouse_x, mouse_y }, { static_cast< int >( checkbox_x - font_size.x ), checkbox_y },
	                                    { static_cast< int >( font_size.x ), static_cast< int >( font_size.y ) } ) ) {
		if ( g_input.key_state< input::KEY_RELEASED >( VK_LBUTTON ) && !awaiting_keybind ) {
			auto viewport = g_render.get_viewport( );

			int distance = checkbox_y - static_cast< int >( viewport.Y );

			if ( distance < group_height && distance > 0 )
				awaiting_keybind = true;
		}
	}
}
