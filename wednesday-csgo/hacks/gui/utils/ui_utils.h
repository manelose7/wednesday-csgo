#pragma once
#include "../../../utils/console/console.h"
#include "../gui.h"

// sory for naespace spam

namespace gui::easing
{
	template< typename T = float >
	constexpr inline T in_cubic( T x )
	{
		return x * x * x;
	}

	template< typename T = float >
	constexpr inline T in_quint( T x )
	{
		T t2 = x * x;
		return x * t2 * t2;
	}

	template< typename T = float >
	constexpr inline T out_quint( T x )
	{
		const T t2 = ( --x ) * x;
		return 1.f + x * t2 * t2;
	}
} // namespace gui::easing

namespace gui::helpers
{
	std::size_t hash( const std::string_view& name );

	std::vector< std::string > split_string( std::string str, const std::string& delimiter );

	void push_cursor( const math::vec2< int >& to_pos );

	math::vec2< int > pop_cursor( );

	math::vec2< int > last_cursor_pos( );
} // namespace gui::helpers
