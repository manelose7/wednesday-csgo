#include "window.h"

void menu::window::draw( int& window_x, int& window_y, int& size_x, int& size_y )
{
	auto menu_color = g_config.find< color >( _( "menu_color" ) );
	auto menu_font  = g_fonts[ _( "menu_font" ) ];

	g_render.render_filled_rectangle( window_x, window_y, size_x, size_y, color( 12, 12, 12 ) );
	g_render.render_rectangle( window_x + 1, window_y + 1, size_x - 3, size_y - 3, color( 30, 30, 30 ) );

	g_render.render_filled_rectangle( window_x + 3, window_y + 3, size_x - 6, 20, color( 20, 20, 20 ) );

	g_render.render_gradient( window_x + 3, window_y + 22, ( size_x - 6 ) / 2, 1, color( 0, 0, 0, 0 ), menu_color );
	g_render.render_gradient( ( window_x + 3 ) + ( size_x - 6 ) / 2, window_y + 22, ( size_x - 6 ) / 2, 1, menu_color, color( 0, 0, 0, 0 ) );

	auto font_size = g_render.render_text_size( _( "wednesday.wtf" ), menu_font );

	g_render.render_text( ( window_x + 3 ) + ( size_x - 6 ) / 2, window_y + 5 + static_cast< int >( font_size.y ) / 2,
	                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( "wednesday.wtf" ),
	                      menu_font, color( 255, 255, 255 ) );

	math::vec2 window_inset = { window_x + 3, window_y + 24 };

	g_render.render_filled_rectangle( window_inset.x, window_inset.y, size_x - 7, 20, color( 20, 20, 20 ) );
	g_render.render_rectangle( window_inset.x, window_inset.y, size_x - 7, 20, color( 30, 30, 30 ) );

	int current_index = 0;

	for ( auto& tab : tabs )
		tab->draw( window_x, window_y, size_x, size_y, current_index++ );
}

void menu::window::input( int& window_x, int& window_y, int& size_x, int& size_y )
{
	static int last_mouse_x = g_input.mouse.pos.x;
	static int last_mouse_y = g_input.mouse.pos.y;

	allowed_to_drag = true;

	int current_index = 0;

	for ( auto& tab : tabs )
		tab->input( window_x, window_y, size_x, size_y, current_index++ );

	if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) && inside_position( g_input.mouse.pos, { window_x, window_y }, { size_x, size_y } ) &&
	     allowed_to_drag ) {
		dragging = true;

		window_x += g_input.mouse.pos.x - last_mouse_x;
		window_y += g_input.mouse.pos.y - last_mouse_y;
	} else {
		dragging = false;
	}

	last_mouse_x = g_input.mouse.pos.x;
	last_mouse_y = g_input.mouse.pos.y;
}

bool menu::window::inside_position( math::vec2< int > mouse_position, math::vec2< int > window_position, math::vec2< int > window_size )
{
	if ( ( mouse_position - window_position ).x > window_size.x || ( mouse_position - window_position ).y > window_size.y ||
	     ( mouse_position - window_position ).x < 0 || ( mouse_position - window_position ).y < 0 )
		return false;

	return true;
}
