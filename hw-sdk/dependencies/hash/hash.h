#pragma once

// build-time hashing.

constexpr static std::uint32_t default_offset_basis = 0x811C9DC5;
constexpr static std::uint32_t prime                = 0x01000193;

namespace fnv_hashing
{
	template< typename s >
	struct fnv1a;

	template<>
	struct fnv1a< std::uint32_t > {
		constexpr static std::uint32_t hash( const std::string& string, const std::uint32_t val = default_offset_basis )
		{
			return ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
		}

		constexpr static std::uint32_t hash( char const* string, const std::uint32_t val = default_offset_basis )
		{
			return ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
		}

		// FUCKKKKK YOUUUUUUUUUUU

		//static std::string to_string( std::uint32_t hash )
		//{
		//	return std::to_string( hash );
		//}

		constexpr static std::uint32_t hash( wchar_t const* string, const std::uint32_t val = default_offset_basis )
		{
			return ( string[ 0 ] == L'\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
		}
	};
}; // namespace fnv_hashing

using fnv = fnv_hashing::fnv1a< std::uint32_t >;
