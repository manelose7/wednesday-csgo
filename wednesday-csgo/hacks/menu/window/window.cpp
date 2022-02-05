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

	if ( selected_color_picker ) {
		auto& option = g_config.find< color >( selected_color_picker );

		g_render.render_filled_rectangle( color_picker_x, color_picker_y, 152, 152, { 20, 20, 20 } );
		g_render.render_rectangle( color_picker_x + 1, color_picker_y + 1, 149, 149, { 30, 30, 30 } );

		for ( int iterator = 0; iterator < 128 / 4; iterator++ ) {
			bool alt_color = iterator % 2 == 1;

			if ( alt_color ) {
				g_render.render_filled_rectangle( color_picker_x + 141, color_picker_y + 3 + 4 * iterator, 4, 4, { 255, 255, 255, 255 } );
				g_render.render_filled_rectangle( color_picker_x + 145, color_picker_y + 3 + 4 * iterator, 4, 4, { 203, 203, 203, 255 } );
			} else {
				g_render.render_filled_rectangle( color_picker_x + 141, color_picker_y + 3 + 4 * iterator, 4, 4, { 203, 203, 203, 255 } );
				g_render.render_filled_rectangle( color_picker_x + 145, color_picker_y + 3 + 4 * iterator, 4, 4, { 255, 255, 255, 255 } );
			}
		}

		for ( int iterator = 0; iterator < 128; iterator++ ) {
			int vibrance = 100.f * ( ( -( iterator ) + 128 ) / 128.f );

			hsv color_from_hsv{ option.to_hsv( ).h, 0, vibrance, 255 };
			hsv color_to_hsv{ option.to_hsv( ).h, 100, vibrance, 255 };

			color color_from = color_from_hsv.to_color( );
			color color_to   = color_to_hsv.to_color( );

			g_render.render_gradient( color_picker_x + 3, color_picker_y + 3 + iterator, 128, 1, color_from, color_to );

			int hue = 360.f * ( ( -( iterator ) + 128 ) / 128.f );

			hsv color_alt_hsv{ hue, 100, 100, 255 };

			color color_alt = color_alt_hsv.to_color( );

			g_render.render_filled_rectangle( color_picker_x + 132, color_picker_y + 3 + iterator, 8, 1, color_alt );

			int alpha = 255.f * ( iterator / 128.f );

			hsv color_alt_alt_hsv{ option.to_hsv( ).h, 100, 100, alpha };

			color color_alt_alt = color_alt_alt_hsv.to_color( );

			g_render.render_filled_rectangle( color_picker_x + 141, color_picker_y + 3 + iterator, 8, 1, color_alt_alt );
		}

		g_render.render_filled_rectangle( color_picker_x + 3.f, color_picker_y + 3.f + 129.f, 145 / 2, 16, { 20, 20, 20 } );
		g_render.render_rectangle( color_picker_x + 3.f, color_picker_y + 3.f + 129.f, 145 / 2 - 1, 16, { 43, 43, 43 } );

		g_render.render_text( color_picker_x + 3.f + 145.f / 4.f, color_picker_y + 3.f + 129.f + font_size.y / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( "copy" ),
		                      menu_font, color( 255, 255, 255 ) );

		g_render.render_filled_rectangle( color_picker_x + 4.f + 145.f / 2.f, color_picker_y + 3.f + 129.f, 145 / 2, 16, { 20, 20, 20 } );
		g_render.render_rectangle( color_picker_x + 4.f + 145.f / 2.f, color_picker_y + 3.f + 129.f, 145 / 2, 16, { 43, 43, 43 } );

		g_render.render_text( color_picker_x + 3.f + 145.f / 2 + 145.f / 4.f, color_picker_y + 3.f + 129.f + font_size.y / 2,
		                      font_alignment::AL_HORIZONTAL_CENTER | font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_NONE, _( "paste" ),
		                      menu_font, color( 255, 255, 255 ) );

		float vibrance   = -( option.to_hsv( ).v / 100.f ) + 1.f;
		float saturation = option.to_hsv( ).s / 100.f;
		float hue        = -( option.to_hsv( ).h / 360.f ) + 1.f;
		float alpha      = option.to_hsv( ).a / 255.f;

		auto old_viewport = g_render.get_viewport( );

		g_render.set_viewport( { color_picker_x + 3, color_picker_y + 3 }, { 128, 128 } );
		g_render.render_circle( color_picker_x + 3 + ( 128 * saturation ) - 4, color_picker_y + 3 + ( 128 * vibrance ) - 4, 3, 30,
		                        { 203, 203, 203, 255 } );
		g_render.set_viewport( old_viewport );

		g_render.render_rectangle( color_picker_x + 132,
		                           std::clamp( color_picker_y + 3.f + ( 128.f * hue ), color_picker_y + 3.f, color_picker_y + 3.f + 128.f - 4.f ), 7,
		                           3, { 203, 203, 203, 255 } );
		g_render.render_rectangle( color_picker_x + 141,
		                           std::clamp( color_picker_y + 3.f + ( 128.f * alpha ), color_picker_y + 3.f, color_picker_y + 3.f + 128.f - 4.f ),
		                           7, 3, { 203, 203, 203, 255 } );
	}
}

void menu::window::input( int& window_x, int& window_y, int& size_x, int& size_y )
{
	static int last_mouse_x = g_input.mouse.pos.x;
	static int last_mouse_y = g_input.mouse.pos.y;
	int mouse_x             = g_input.mouse.pos.x;
	int mouse_y             = g_input.mouse.pos.y;

	allowed_to_drag = true;

	int current_index = 0;

	if ( selected_color_picker && g_input.key_state< input::KEY_RELEASED >( VK_LBUTTON ) &&
	     !inside_position( { mouse_x, mouse_y }, { color_picker_x, color_picker_y }, { 152, 152 } ) ) {
		selected_color_picker = { };
		color_picker_x        = { };
		color_picker_y        = { };
	}

	if ( selected_color_picker ) {
		auto& option = g_config.find< color >( selected_color_picker );

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) && !dragging_hue_color_picker && !dragging_alpha_color_picker ) {
			if ( inside_position( { mouse_x, mouse_y }, { color_picker_x + 3, color_picker_y }, { 128, 128 } ) || dragging_picker_color_picker ) {
				dragging_picker_color_picker = true;

				float saturation = ( mouse_x - color_picker_x + 3.f ) / 128.f;
				float vibrance   = ( mouse_y - color_picker_y + 3.f ) / 128.f;

				if ( vibrance < 0.f )
					vibrance = 0.f;
				else if ( vibrance > 1.f )
					vibrance = 1.f;

				if ( saturation < 0.f )
					saturation = 0.f;
				else if ( saturation > 1.f )
					saturation = 1.f;

				vibrance = -( vibrance ) + 1.f;

				hsv buffer_hsv = option.to_hsv( );
				option = hsv{ buffer_hsv.h, static_cast< int >( 100 * saturation ), static_cast< int >( 100 * vibrance ), buffer_hsv.a }.to_color( );
			}
		} else {
			dragging_picker_color_picker = false;
		}

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) && !dragging_picker_color_picker && !dragging_alpha_color_picker ) {
			if ( inside_position( { mouse_x, mouse_y }, { color_picker_x + 132, color_picker_y + 3 }, { 8, 128 } ) || dragging_hue_color_picker ) {
				dragging_hue_color_picker = true;

				float hue = ( mouse_y - color_picker_y + 3.f ) / 128.f;

				if ( hue < 0.f )
					hue = 0.f;
				else if ( hue > 1.f )
					hue = 1.f;

				hue = -( hue ) + 1.f;

				hsv buffer_hsv = option.to_hsv( );
				option         = hsv{ static_cast< int >( 360.f * hue ), buffer_hsv.s, buffer_hsv.v, buffer_hsv.a }.to_color( );
			}
		} else {
			dragging_hue_color_picker = false;
		}

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) && !dragging_picker_color_picker && !dragging_hue_color_picker ) {
			if ( inside_position( { mouse_x, mouse_y }, { color_picker_x + 141, color_picker_y + 3 }, { 8, 128 } ) || dragging_alpha_color_picker ) {
				dragging_alpha_color_picker = true;

				float alpha = ( mouse_y - color_picker_y + 3.f ) / 128.f;

				if ( alpha < 0.f )
					alpha = 0.f;
				else if ( alpha > 1.f )
					alpha = 1.f;

				hsv buffer_hsv = option.to_hsv( );
				option         = hsv{ buffer_hsv.h, buffer_hsv.s, buffer_hsv.v, static_cast< int >( 255.f * alpha ) }.to_color( );
			}
		} else {
			dragging_alpha_color_picker = false;
		}

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) ) {
			if ( inside_position( { mouse_x, mouse_y }, { color_picker_x + 3, color_picker_y + 3 + 129 }, { 145 / 2 - 1, 16 } ) ) {
				copied_color = option;
			}
			if ( inside_position( { mouse_x, mouse_y }, { color_picker_x + 4 + 145 / 2, color_picker_y + 3 + 129 }, { 145 / 2, 16 } ) ) {
				option = copied_color;
			}
		}
	} else {
		dragging_picker_color_picker = false;
		dragging_hue_color_picker = false;
		dragging_alpha_color_picker = false;
	}

	if ( !resizing && !dragging_picker_color_picker && !dragging_hue_color_picker && !dragging_alpha_color_picker &&
	     !inside_position( { mouse_x, mouse_y }, { color_picker_x, color_picker_y }, { 152, 152 } ) )
		for ( auto& tab : tabs )
			tab->input( window_x, window_y, size_x, size_y, current_index++ );

	auto& menu_size_x = g_config.find< int >( _( "menu_size_x" ) );
	auto& menu_size_y = g_config.find< int >( _( "menu_size_y" ) );

	if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) && !dragging_picker_color_picker && !dragging_hue_color_picker &&
	     !dragging_alpha_color_picker ) {
		if ( inside_position( g_input.mouse.pos, { window_x, window_y }, { size_x, size_y } ) && allowed_to_drag && !dragging || resizing ) {
			if ( inside_position( g_input.mouse.pos, { window_x + size_x - 10, window_y + size_y - 10 }, { 10, 10 } ) || resizing ) {
				resizing = true;

				menu_size_x += g_input.mouse.pos.x - last_mouse_x;
				menu_size_y += g_input.mouse.pos.y - last_mouse_y;

				menu_size_x = std::clamp( menu_size_x, 400, 1000 );
				menu_size_y = std::clamp( menu_size_y, 500, 1000 );
			} else {
				window_x += g_input.mouse.pos.x - last_mouse_x;
				window_y += g_input.mouse.pos.y - last_mouse_y;

				window_x = std::clamp( window_x, 0, g_ctx.screen_size.x - size_x );
				window_y = std::clamp( window_y, 0, g_ctx.screen_size.y - size_y );
			}
		}
	} else {
		resizing = false;
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
