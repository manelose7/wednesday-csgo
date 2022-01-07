#pragma once

#include "../hash/hash.h"
#include <immintrin.h>
// build-time string xoring.

// warning C4172: returning address of local variable or temporary
#pragma warning( disable : 4172 )

#define GET_XOR_KEYUI8  ( ( fnv::hash( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT8_MAX )
#define GET_XOR_KEYUI16 ( ( fnv::hash( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT16_MAX )
#define GET_XOR_KEYUI32 ( ( fnv::hash( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT32_MAX )

namespace __xor
{
	namespace xor_float
	{
		constexpr std::uint32_t gen_key( )
		{
			return ( ~( __TIME__[ 0 ] * 0xa24a7c ) ^ 0xcfc9 ^ ( __TIME__[ 4 ] * 0x5a99 ) ^ 0x57f3aaa9 ^ ~( __TIME__[ 6 ] * 0x84575a ) ^ 0x51f6 ^
			         ( __TIME__[ 3 ] * 0x1cd2 ) ^ 0x7dee4b90 ^ ~( __TIME__[ 7 ] * 0x38ab64 ) ^ 0x661198b );
		}

		constexpr std::uint32_t xor_key = ::__xor::xor_float::gen_key( );

		__forceinline float convert_back( const std::uint32_t val )
		{
			const auto xor_key_m128   = _mm_castsi128_ps( _mm_cvtsi32_si128( ::__xor::xor_float::xor_key ) );
			const auto val_m128       = _mm_castsi128_ps( _mm_cvtsi32_si128( val ) );
			const auto xored_val_m128 = _mm_xor_ps( val_m128, xor_key_m128 );

			return _mm_cvtss_f32( xored_val_m128 );
		}
		__forceinline float convert( const float val )
		{
			std::uint32_t cache{ };
			reinterpret_cast< float& >( cache ) = val;
			cache ^= ::__xor::xor_float::xor_key;

			return xor_float::convert_back( cache );
		}
		__forceinline uint32_t encrypt( const float val )
		{
			std::uint32_t cache{ };
			reinterpret_cast< float& >( cache ) = val;
			cache ^= ::__xor::xor_float::xor_key;

			return cache;
		}
	} // namespace xor_float
	template< class t, const size_t len, const t key >
	class gen
	{
	private:
		std::array< t, len > m_buffer;

	private:
		constexpr t enc( const t c ) const noexcept
		{
			return c ^ key;
		}
		__forceinline t dec( const t c ) const noexcept
		{
			return c ^ key;
		}

	public:
		__forceinline auto data( ) noexcept
		{
			for ( size_t i{ 0u }; i < len; ++i )
				m_buffer[ i ] = dec( m_buffer[ i ] );

			return m_buffer.data( );
		}

		template< size_t... seq >
		constexpr __forceinline gen( const t ( &s )[ len ], std::index_sequence< seq... > ) noexcept : m_buffer{ enc( s[ seq ] )... }
		{
		}
	};
} // namespace __xor

template< class t, const size_t len >
constexpr __forceinline auto __xor_string( const t ( &s )[ len ] )
{
	return __xor::gen< t, len, GET_XOR_KEYUI8 >( s, std::make_index_sequence< len >( ) ).data( );
}
