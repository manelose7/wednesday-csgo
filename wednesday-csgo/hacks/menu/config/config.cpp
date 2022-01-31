#include "config.h"

bool config::impl::init( )
{
	return true;
}

void config::impl::insert( std::uint32_t hash, option _option )
{
	settings.insert( std::make_pair( hash, _option ) );
}

void config::impl::insert( std::string string, option _option )
{
	settings.insert( std::make_pair( HASH( string.c_str( ) ), _option ) );
}
