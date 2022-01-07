#pragma once
#include "../includes/includes.h"
#include <map>
#include <string>

namespace gui::groupbox
{
	struct impl {
		void invoke_groupbox( const std::string& name, const math::vec2< int > pos, const math::vec2< int > size );
		void end_groupbox( );

	private:
		int m_id;
		math::vec2< int > m_pos;
		math::vec2< int > m_size;
		math::vec2< int > m_cursor_pos;

		// scrolling
		std::map< int, float > m_scrolling;
		std::map< int, float > m_previous_scrolling;
		std::map< std::size_t, std::pair< float, bool > > m_should_scroll;
	};
} // namespace gui::groupbox

inline gui::groupbox::impl g_groupbox;
