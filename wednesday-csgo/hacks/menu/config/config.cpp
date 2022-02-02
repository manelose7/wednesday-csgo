#include "config.h"
#include "../../../dependencies/json/json.hpp"

bool config::impl::init( )
{
	return true;
}

void config::impl::save( std::string path )
{
	using namespace nlohmann;

	json reader;

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.bool_value;
			break;
		case variable_type::VARIABLE_INT:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.int_value;
			break;

		case variable_type::VARIABLE_FLOAT:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.float_value;
			break;

		case variable_type::VARIABLE_COLOR:
			reader[ fnv_hashing::hashes[ setting.first ] ] = { setting.second.color_value.r, setting.second.color_value.g,
				                                               setting.second.color_value.b, setting.second.color_value.a };
			break;

		case variable_type::VARIABLE_STRING:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.string_value;
			break;
		}
	}

	std::ofstream stream( path );

	stream << std::setw( 4 ) << reader << std::endl;

	stream.close( );
}

void config::impl::load( std::string path )
{
	using namespace nlohmann;

	json reader{ };

	std::ifstream stream( path );

	stream >> reader;

	stream.close( );

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			setting.second.bool_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;
		case variable_type::VARIABLE_INT:
			setting.second.int_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;

		case variable_type::VARIABLE_FLOAT:
			setting.second.float_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;

		case variable_type::VARIABLE_COLOR:
			setting.second.color_value.r = reader[ fnv_hashing::hashes[ setting.first ] ][ 0 ];
			setting.second.color_value.g = reader[ fnv_hashing::hashes[ setting.first ] ][ 1 ];
			setting.second.color_value.b = reader[ fnv_hashing::hashes[ setting.first ] ][ 2 ];
			setting.second.color_value.a = reader[ fnv_hashing::hashes[ setting.first ] ][ 3 ];

			break;

		case variable_type::VARIABLE_STRING:
			setting.second.string_value = reader[ fnv_hashing::hashes[ setting.first ] ];

			break;
		}
	}
}

void config::impl::insert( std::uint32_t hash, option _option )
{
	settings.insert( std::make_pair( hash, _option ) );
}

void config::impl::insert( std::string string, option _option )
{
	settings.insert( std::make_pair( HASH( string.c_str( ) ), _option ) );
}
