#include "groupbox.h"
#include "../../../utils/renderer/renderer.h"
#include "../includes/includes.h"
#include "../utils/ui_utils.h"

void gui::groupbox::impl::invoke_groupbox( const std::string& name, const math::vec2< int > pos, const math::vec2< int > size )
{
	// get groupbox id
	const auto my_id = gui::helpers::hash( name );
	m_id             = my_id;

	math::vec2< int > cursor_pos = gui::helpers::pop_cursor( );
	math::vec2< int > group_size{ };

	math::vec2< int > draw_pos = g_gui.position + cursor_pos + pos;

	g_render.render_filled_rectangle( draw_pos - 1, group_size + 2, gui::pallete::third_outline( ) );
	math::vec2< int > final_pos = { cursor_pos + pos + math::vec2< int >( 20, 41 ) };

	gui::helpers::push_cursor( final_pos );
}
