#pragma once
#include <unordered_map>

// build-time hashing.

constexpr static std::uint32_t default_offset_basis = 0x811C9DC5;
constexpr static std::uint32_t prime                = 0x01000193;

namespace fnv_hashing
{

	inline std::unordered_map< std::uint32_t, std::string > hashes{ };

	template< typename s >
	struct fnv1a;

	template<>
	struct fnv1a< std::uint32_t > {
		constexpr static std::uint32_t hash( const std::string& string, const std::uint32_t val = default_offset_basis )
		{
			auto temp_hash      = ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
			hashes[ temp_hash ] = string;

			return temp_hash;
		}

		constexpr static std::uint32_t hash( char const* string, const std::uint32_t val = default_offset_basis )
		{
			auto temp_hash      = ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
			hashes[ temp_hash ] = string;

			return temp_hash;
		}

		// FUCKKKKK YOUUUUUUUUUUU

		// static std::string to_string( std::uint32_t hash )
		//{
		//	return std::to_string( hash );
		// }

		constexpr static std::uint32_t hash( wchar_t const* string, const std::uint32_t val = default_offset_basis )
		{
			auto temp_hash        = ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
			//auto temp_wide_string = std::wstring( string );

			//hashes[ temp_hash ] = std::string( temp_wide_string.begin( ), temp_wide_string.end( ) );

			return temp_hash;
		}
	};
}; // namespace fnv_hashing

using fnv = fnv_hashing::fnv1a< std::uint32_t >;
