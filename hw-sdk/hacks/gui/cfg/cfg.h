#pragma once
#include "../../../game/sdk/structs/color.h"
#include "../../../utils/console/console.h"
#include <cstdint>
#include <unordered_map>

namespace configs
{
	// max alpha = 255
	// own alpha = actual variable alpha
	// gui alpha = gui's current alpha
	enum alpha_type
	{
		MAX_ALPHA = 0,
		OWN_ALPHA,
		GUI_ALPHA
	};

	enum class variable_type_t : std::int32_t
	{
		TYPE_BOOL = 0,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_MAX
	};

	struct variable_t {
	public:
		std::uint32_t hash{ };
		configs::variable_type_t variable_type{ };

		// values
		bool as_bool{ };
		int as_int{ };
		float as_float{ };

		// ctors
		variable_t( int value, std::uint32_t hashed ) : hash( hashed ), as_int( value ), variable_type( variable_type_t::TYPE_INT ){ };

		variable_t( bool value, std::uint32_t hashed ) : hash( hashed ), as_bool( value ), variable_type( variable_type_t::TYPE_BOOL ){ };

		variable_t( float value, std::uint32_t hashed ) : hash( hashed ), as_float( value ), variable_type( variable_type_t::TYPE_FLOAT ){ };
	};

	struct impl {
	public:
		static inline std::unordered_map< std::uint32_t, configs::variable_t > variable_map;

		bool init( );

		template< typename T >
		static T& get( std::uint32_t hash );

		template< typename T >
		const T& operator[]( std::uint32_t hash )
		{
			return get< T >( hash );
		}

		template< alpha_type alpha >
		color as_color( const std::string& color_name );
	};
} // namespace configs

inline configs::impl g_cfg;

#include "cfg.inl"
