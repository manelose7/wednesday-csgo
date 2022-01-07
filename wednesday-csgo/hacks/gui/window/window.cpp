#include "window.h"
#include "../../../globals/ctx/ctx.h"
#include "../cfg/cfg.h"
#include "../utils/ui_utils.h"

// im so sorry about this
#define AIMBOT_TAB_BOUNDING    tab_util.pos + math::vec2< int >( 3, 3 ), math::vec2< int >( m_tab_width - 2, 33 )
#define AIMBOT_ACCENT_BOUNDING tab_util.pos + math::vec2< int >( 3, 34 ), math::vec2< int >( m_tab_width - 2, 2 )

#define VISUALS_TAB_BOUNDING    tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width ), 3 ), math::vec2< int >( m_tab_width - 2, 33 )
#define VISUALS_ACCENT_BOUNDING tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width ), 34 ), math::vec2< int >( m_tab_width - 2, 2 )

#define MISC_TAB_BOUNDING tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 2 ), 3 ), math::vec2< int >( m_tab_width - 2, 33 )
#define MISC_ACCENT_BOUNDING                                                                                                                         \
	tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 2 ), 34 ), math::vec2< int >( m_tab_width - 2, 2 )

#define SKINS_TAB_BOUNDING tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 3 ), 3 ), math::vec2< int >( m_tab_width - 2, 33 )
#define SKINS_ACCENT_BOUNDING                                                                                                                        \
	tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 3 ), 34 ), math::vec2< int >( m_tab_width - 2, 2 )

#define DEMOS_TAB_BOUNDING tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 4 ), 3 ), math::vec2< int >( m_tab_width - 2, 33 )
#define DEMOS_ACCENT_BOUNDING                                                                                                                        \
	tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 4 ), 34 ), math::vec2< int >( m_tab_width - 2, 2 )

#define CONFIG_TAB_BOUNDING tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 5 ), 3 ), math::vec2< int >( m_tab_width - 5, 33 )
#define CONFIG_ACCENT_BOUNDING                                                                                                                       \
	tab_util.pos + math::vec2< int >( 3 + static_cast< int >( m_tab_width * 5 ), 34 ), math::vec2< int >( m_tab_width - 5, 2 )

void gui::elements::window_impl::util_t::draw_background( )
{
	// render all 3 menu outlines
	g_render.render_filled_rectangle< int >( g_gui.position, g_gui.size, gui::pallete::first_outline( ) );
	g_render.render_filled_rectangle< int >( g_gui.position + 2, g_gui.size - 4, gui::pallete::second_outline( ) );
	g_render.render_filled_rectangle< int >( g_gui.position + math::vec2< int >( 4, 36 ), g_gui.size - math::vec2< int >( 8, 40 ),
	                                         gui::pallete::third_outline( ) );

	// render menu's main gradient
	g_render.render_gradient< gradient_type_t::VERTICAL, int >( g_gui.position + math::vec2< int >( 6, 38 ),
	                                                            math::vec2< int >( g_gui.size.x - 12, g_gui.size.y - 44 ),
	                                                            color( 32, 32, 32, g_gui.main.alpha ), color( 24, 24, 24, g_gui.main.alpha ) );
}

void gui::elements::window_impl::util_t::draw_title_header( )
{
	// black header outline
	g_render.render_filled_rectangle< int >( g_gui.position + 2, math::vec2< int >( g_gui.size.x - 4, 32 ), gui::pallete::first_outline( ) );
	// grey header outline
	g_render.render_filled_rectangle< int >( g_gui.position + 2, math::vec2< int >( g_gui.size.x - 4, 30 ), gui::pallete::second_outline( ) );
	// gradient
	g_render.render_gradient< gradient_type_t::VERTICAL, int >( g_gui.position + 4, math::vec2< int >( g_gui.size.x - 8, 26 ),
	                                                            color( 27, 27, 27, g_gui.main.alpha ), color( 17, 17, 17, g_gui.main.alpha ) );
}

void gui::elements::window_impl::util_t::handle_drag( bool hover, const math::vec2< int >& delta )
{
	if ( !g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) && hover )
		g_gui.main.dragging = true;
	else if ( g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) ) {
		g_gui.position += delta;

		// g_gui.position.x = std::clamp< int >( g_gui.position.x, 0, g_ctx.screen_size.x - g_gui.size.x );
		// g_gui.position.y = std::clamp< int >( g_gui.position.y, 0, g_ctx.screen_size.y - g_gui.size.y );
	} else if ( g_gui.main.dragging && !g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
		g_gui.main.dragging = false;
}

void gui::elements::window_impl::util_t::handle_resize( bool hover )
{
	if ( !g_gui.main.resizing && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) && hover )
		g_gui.main.resizing = true;
	else if ( g_gui.main.resizing && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) ) {
		g_gui.size = g_input.mouse.pos - g_gui.position;

		g_gui.size.x = std::clamp< int >( g_gui.size.x, 537, 900 );
		g_gui.size.y = std::clamp< int >( g_gui.size.y, 621, 800 );

	} else if ( g_gui.main.resizing && !g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
		g_gui.main.resizing = false;
}

bool gui::elements::window_impl::invoke_window( const std::string_view name )
{
	static math::vec2< int > old_mouse_pos;
	math::vec2< int > delta = g_input.mouse.pos - old_mouse_pos;
	// menu was toggled
	if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( open_key ) ) {
		// main window alpha lower then max alpha
		if ( g_gui.main.alpha <= color::MAX_ALPHA ) {
			// reset element focused id
			if ( g_gui.focused_id != UNFOCUSED )
				g_gui.focused_id = UNFOCUSED;
			// reset dragging flag
			if ( g_gui.main.dragging )
				g_gui.main.dragging = false;
		}

		// switch between open and closed once menu key was released
		g_gui.main.open = !g_gui.main.open;
	}

	// handle menu alpha
	if ( g_gui.main.open ) {
		ui_anim_state += ( 1.0f / 0.25f ) * g_interfaces.globals->frame_time;
		ui_anim_state = std::clamp( ui_anim_state, 0.f, 1.f );

		g_gui.main.alpha = std::clamp< float >( gui::easing::out_quint( ui_anim_state ) * 255.f, 0.f, 255.f );
	} else {
		ui_anim_state -= ( 1.0f / 0.25f ) * g_interfaces.globals->frame_time;
		ui_anim_state = std::clamp( ui_anim_state, 0.f, 1.f );

		g_gui.main.alpha = std::clamp< float >( gui::easing::in_quint( ui_anim_state ) * 255.f, 0.f, 255.f );
	}

	// square around the menu so we dont drag only with title header (mess)
	moveable_area_hovered = g_input.mouse.in_params( g_gui.position, math::vec2< int >( g_gui.size.x, 48 ) ) ||
	                        g_input.mouse.in_params( g_gui.position, math::vec2< int >( 22, g_gui.size.y ) ) ||
	                        g_input.mouse.in_params( math::vec2< int >( g_gui.position.x, g_gui.position.y + g_gui.size.y - 30 ),
	                                                 math::vec2< int >( g_gui.size.x - 30, 30 ) ) ||
	                        g_input.mouse.in_params( math::vec2< int >( g_gui.position.x + g_gui.size.x - 30, g_gui.position.y ),
	                                                 math::vec2< int >( 30, g_gui.size.y - 30 ) );
	// square on bottom right menu
	resize_area_hovered = g_input.mouse.in_params( g_gui.position + ( g_gui.size - math::vec2< int >( 30, 30 ) ), math::vec2< int >( 35, 35 ) );

	// make sure we're not focused on any elements to move menu
	if ( g_gui.focused_id == UNFOCUSED ) {
		// handle dragging
		utils.handle_drag( moveable_area_hovered, delta );

		// handle resizing
		utils.handle_resize( resize_area_hovered );
	}

	utils.draw_background( );

	utils.draw_title_header( );

	// render text and add a .vip next to it.
	g_render.render_text( g_gui.position + math::vec2< int >( 12, 10 ), font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE_SEMI, name.data( ),
	                      g_fonts[ HASH( "main_font_bold" ) ], gui::pallete::white( ) );

	g_render.render_text( g_gui.position +
	                          math::vec2< int >( 13 + g_render.render_text_size( name.data( ), g_fonts[ HASH( "main_font_bold" ) ] ).x, 10 ),
	                      font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE_SEMI, _( ".wtf" ), g_fonts[ HASH( "main_font_bold" ) ],
	                      g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );

	// swap stack
	std::stack< math::vec2< int > >( ).swap( g_gui.cursor_pos_stack );

	// just a random number for now but this is were elements should be starting to draw from starting window position
	gui::helpers::push_cursor( { 20, 60 } );

	old_mouse_pos = g_input.mouse.pos;

	return true;
}

void gui::elements::window_impl::end_window( )
{
	// draw tabs
	g_tabs.think( );
}

// [#] tabs

void gui::tabs::impl::invoke_tabs( const std::vector< std::string_view > m_tabs )
{
	g_gui.tabs = m_tabs;
}

void gui::tabs::impl::think( )
{
	struct {
		math::vec2< int > pos  = { g_gui.position.x + 22, g_gui.position.y + 48 };
		math::vec2< int > size = { g_gui.size.x - 44, 39 };
	} tab_util;

	std::array< bool, 6 > m_in_tab_area = { };

	auto select_tab = [ &m_in_tab_area]( int tab_index ) constexpr
	{
		for ( std::int32_t i = 0; i <= 5; i++ )
			i != tab_index ? m_in_tab_area[ i ] = false : m_in_tab_area[ i ] = true;
	};

	// draw background
	{
		g_render.render_filled_rectangle( tab_util.pos, tab_util.size, gui::pallete::first_outline( ) );
		g_render.render_filled_rectangle( tab_util.pos + 1, tab_util.size - 2, gui::pallete::second_outline( ) );
		g_render.render_filled_rectangle( tab_util.pos + 2, tab_util.size - 4, gui::pallete::third_outline( ) );
		g_render.render_gradient< gradient_type_t::VERTICAL, int >( tab_util.pos + 3, tab_util.size - 6, color( 25, 25, 25, g_gui.main.alpha ),
		                                                            color( 17, 17, 17, g_gui.main.alpha ) );
	}

	const int m_tab_width = static_cast< int >( tab_util.size.x / 6.f );
	// do tab selection
	if ( g_gui.focused_id == UNFOCUSED ) {
		if ( g_input.mouse.in_params( AIMBOT_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::AIMBOT );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::AIMBOT;
		} else if ( g_input.mouse.in_params( VISUALS_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::VISUALS );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::VISUALS;
		} else if ( g_input.mouse.in_params( MISC_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::MISC );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::MISC;
		} else if ( g_input.mouse.in_params( SKINS_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::SKINS );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::SKINS;
		} else if ( g_input.mouse.in_params( DEMOS_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::DEMOS );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::DEMOS;
		} else if ( g_input.mouse.in_params( CONFIG_TAB_BOUNDING ) ) {
			select_tab( gui::tabs::tab_index::CONFIG );
			if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
				current_tab = gui::tabs::tab_index::CONFIG;
		}
	}

	const color selected_a = color( 15, 15, 15, g_gui.main.alpha );
	const color selected_b = color( 28, 28, 28, g_gui.main.alpha );

	switch ( current_tab ) {
		// c++ 20 thanks
		using enum gui::tabs::tab_index;
	case AIMBOT:
		g_render.render_gradient< gradient_type_t::VERTICAL >( AIMBOT_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( AIMBOT_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	case VISUALS:
		g_render.render_gradient< gradient_type_t::VERTICAL >( VISUALS_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( VISUALS_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	case MISC:
		g_render.render_gradient< gradient_type_t::VERTICAL >( MISC_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( MISC_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	case SKINS:
		g_render.render_gradient< gradient_type_t::VERTICAL >( SKINS_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( SKINS_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	case DEMOS:
		g_render.render_gradient< gradient_type_t::VERTICAL >( DEMOS_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( DEMOS_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	case CONFIG:
		g_render.render_gradient< gradient_type_t::VERTICAL >( CONFIG_TAB_BOUNDING, selected_a, selected_b );
		g_render.render_filled_rectangle( CONFIG_ACCENT_BOUNDING, g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );
		break;
	}

	for ( std::int32_t i = 0; i <= 5; i++ ) {
		if ( i > 0 )
			g_render.render_filled_rectangle< int >( tab_util.pos + math::vec2< int >( 1 + ( tab_util.size.x / 6 ) * i, 3 ),
			                                         math::vec2< int >( 2, 33 ), color( 38, 35, 38, g_gui.main.alpha ) );
		// cancer
		const int a                      = tab_util.pos.x + ( 1 + ( tab_util.size.x / 6 ) * ( i + 1 ) );
		const int b                      = tab_util.pos.x + ( 1 + ( tab_util.size.x / 6 ) * i );
		math::vec2< int > final_position = math::vec2< int >( ( a + b ) / 2, tab_util.pos.y + 14 );

		g_render.render_text( final_position, font_alignment::AL_HORIZONTAL_CENTER, font_flags::FLAG_OUTLINE_SEMI, g_gui.tabs[ i ].data( ),
		                      g_fonts[ HASH( "main_font" ) ], gui::pallete::white( ) );
	}
}
