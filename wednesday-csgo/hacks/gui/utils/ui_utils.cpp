#include "ui_utils.h"

math::vec2< int > last_cursor_position{ };

std::size_t gui::helpers::hash( const std::string_view& name )
{
	return std::hash< std::string_view >( )( name );
};

std::vector< std::string > gui::helpers::split_string( std::string str, const std::string& delimiter )
{
	std::vector< std::string > output;

	size_t pos = 0;
	while ( ( pos = str.find( delimiter ) ) != std::string::npos ) {
		std::string token = str.substr( 0, pos );
		output.push_back( token );
		str.erase( 0, pos + delimiter.length( ) );
	}

	output.push_back( str );

	return output;
}

void gui::helpers::push_cursor( const math::vec2< int >& to_pos )
{
	g_gui.cursor_pos_stack.push( to_pos );
}

math::vec2< int > gui::helpers::pop_cursor( )
{
	// return empty vector if we dont have cursor pos
	if ( g_gui.cursor_pos_stack.empty( ) ) {
		console::print< console::log_level::WARNING >( _( "{} returned 0 - g_gui.cursor_pos_stack was empty." ), __func__ );
		return { };
	}

	math::vec2< int > top{ g_gui.cursor_pos_stack.top( ) };
	g_gui.cursor_pos_stack.pop( );
	last_cursor_position = top;
	return top;
}

math::vec2< int > gui::helpers::last_cursor_pos( )
{
	return last_cursor_position;
}
