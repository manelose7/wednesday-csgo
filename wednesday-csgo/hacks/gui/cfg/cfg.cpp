#include "cfg.h"
#include "../../../dependencies/mocking_bird/mocking_bird.h"
#include "../../../globals/macros/macros.h"

#define CFG_EMPLACE( variable_type, name ) configs::impl::variable_map.emplace( name, configs::variable_t( variable_type, name ) );

#define COLOR_EMPLACE_A( col, name )                                                                                                                 \
	CFG_EMPLACE( static_cast< int >( col.r ), HASH( name "_r" ) )                                                                                    \
	CFG_EMPLACE( static_cast< int >( col.g ), HASH( name "_g" ) )                                                                                    \
	CFG_EMPLACE( static_cast< int >( col.b ), HASH( name "_b" ) )                                                                                    \
	CFG_EMPLACE( static_cast< int >( col.a ), HASH( name "_a" ) )

#define COLOR_EMPLACE( col, name )                                                                                                                   \
	CFG_EMPLACE( static_cast< int >( col.r ), HASH( name "_r" ) )                                                                                    \
	CFG_EMPLACE( static_cast< int >( col.g ), HASH( name "_g" ) )                                                                                    \
	CFG_EMPLACE( static_cast< int >( col.b ), HASH( name "_b" ) )

bool configs::impl::init( )
{
	MOCKING_TRY

	COLOR_EMPLACE_A( color( 148, 123, 237, 255 ), "main_menu_color" );

	MOCKING_CATCH( return false );

	console::print< console::log_level::DEBUG >( _( "Initialized {} config variables." ), configs::impl::variable_map.size( ) );

	return true;
}
