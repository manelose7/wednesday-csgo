#pragma once

#include <deque>

#include "../../../globals/includes/includes.h"
#include "../../../utils/renderer/renderer.h"

namespace config
{
	enum class variable_type : int
	{
		VARIABLE_BOOL,
		VARIABLE_INT,
		VARIABLE_FLOAT,
		VARIABLE_COLOR,
		VARIABLE_STRING,
		VARIABLE_MAX
	};

	struct option {
		variable_type type{ };

		bool bool_value{ };

		int int_value{ };

		float float_value{ };

		float min_slider_value{ };
		float max_slider_value{ };

		color color_value{ };

		std::string string_value{ };

		option( bool value )
		{
			this->type       = variable_type::VARIABLE_BOOL;
			this->bool_value = value;
		}

		option( int value, int min, int max )
		{
			this->type             = variable_type::VARIABLE_INT;
			this->int_value        = value;
			this->min_slider_value = static_cast< float >( min );
			this->max_slider_value = static_cast< float >( max );
		}

		option( float value, float min, float max )
		{
			this->type             = variable_type::VARIABLE_FLOAT;
			this->float_value      = value;
			this->min_slider_value = min;
			this->max_slider_value = max;
		}

		option( color value )
		{
			this->type        = variable_type::VARIABLE_COLOR;
			this->color_value = value;
		}

		option( std::string value )
		{
			this->type         = variable_type::VARIABLE_STRING;
			this->string_value = value;
		}
	};

	struct impl {
		std::unordered_map< std::int32_t, option > settings{ };

		bool init( );

		void save( std::string path );
		void load( std::string path );

		void insert( std::uint32_t hash, option _option );
		void insert( std::string name, option _option );

		template< typename T >
		T& find( std::uint32_t hash )
		{
			auto found_option = settings.find( hash );

			if ( !found_option._Ptr )
				return *reinterpret_cast< T* >( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_BOOL:
				return ( T& )( found_option->second.bool_value );
			case variable_type::VARIABLE_INT:
				return ( T& )( found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				return ( T& )( found_option->second.float_value );
			case variable_type::VARIABLE_COLOR:
				return ( T& )( found_option->second.color_value );
			case variable_type::VARIABLE_STRING:
				return ( T& )( found_option->second.string_value );
			}

			return *reinterpret_cast< T* >( nullptr );
		}

		template< typename T >
		T& find( std::string name )
		{
			auto found_option = settings.find( HASH( name ) );

			if ( !found_option._Ptr )
				return *reinterpret_cast< T* >( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_BOOL:
				return ( T& )( found_option->second.bool_value );
			case variable_type::VARIABLE_INT:
				return ( T& )( found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				return ( T& )( found_option->second.float_value );
			case variable_type::VARIABLE_COLOR:
				return ( T& )( found_option->second.color_value );
			case variable_type::VARIABLE_STRING:
				return ( T& )( found_option->second.string_value );
			}

			return *reinterpret_cast< T* >( nullptr );
		}

		template< typename T >
		T& find( std::uint32_t hash, T& min, T& max )
		{
			auto found_option = settings.find( hash );

			if ( !found_option._Ptr )
				return *reinterpret_cast< T* >( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_INT:
				min = ( T )( found_option->second.min_slider_value );
				max = ( T )( found_option->second.max_slider_value );

				return ( T& )( found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				min = ( T )( found_option->second.min_slider_value );
				max = ( T )( found_option->second.max_slider_value );

				return ( T& )( found_option->second.float_value );
			}

			return *reinterpret_cast< T* >( nullptr );
		}

		template< typename T >
		T& find( std::string name, T& min, T& max )
		{
			auto found_option = settings.find( HASH( name ) );

			if ( !found_option._Ptr )
				return *reinterpret_cast< T* >( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_INT:
				min = ( T& )( found_option->second.min_slider_value );
				max = ( T& )( found_option->second.max_slider_value );

				return ( T& )( found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				min = ( T& )( found_option->second.min_slider_value );
				max = ( T& )( found_option->second.max_slider_value );

				return ( T& )( found_option->second.float_value );
			}

			return *reinterpret_cast< T* >( nullptr );
		}
	};
} // namespace config

inline config::impl g_config;
