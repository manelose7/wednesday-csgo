#include "cfg.h"
#include "../gui_ctx/gui_ctx.h"

template< typename T >
static T& configs::impl::get( std::uint32_t hash )
{
	const auto value = variable_map.find( hash );

	if ( !value._Ptr )
		return *( T* )nullptr;

	switch ( value._Ptr->_Myval.second.variable_type ) {
	case variable_type_t::TYPE_BOOL:
		return *( T* )&value._Ptr->_Myval.second.as_bool;
	case variable_type_t::TYPE_INT:
		return *( T* )&value._Ptr->_Myval.second.as_int;
	case variable_type_t::TYPE_FLOAT:
		return *( T* )&value._Ptr->_Myval.second.as_float;
	case variable_type_t::TYPE_MAX:
		return *( T* )nullptr;
	}

	console::print< console::log_level::FATAL >( "Config '{}' failed - [ hash {} ]", __func__, hash );

	return *( T* )nullptr;
}

template< configs::alpha_type alpha >
color configs::impl::as_color( const std::string& color_name )
{
	// separate our names into strings.
	std::string m_r = color_name + _( "_r" ), m_g = color_name + _( "_g" ), m_b = color_name + _( "_b" ), m_a = color_name + _( "_a" );
	// setup values into our color struct.
	color return_color = color( get< int >( HASH( m_r.data( ) ) ), get< int >( HASH( m_g.data( ) ) ), get< int >( HASH( m_b.data( ) ) ) );

	// return with color based on alpha type chosen
	switch ( alpha ) {
	case alpha_type::MAX_ALPHA:
		return return_color.set_alpha( 255 );
	case alpha_type::OWN_ALPHA:
		return return_color.set_alpha( get< int >( HASH( m_a.data( ) ) ) );
	case alpha_type::GUI_ALPHA:
		return return_color.set_alpha( g_gui.main.alpha );
	};
	return return_color;
}