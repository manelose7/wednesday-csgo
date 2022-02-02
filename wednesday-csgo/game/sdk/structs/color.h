#pragma once
#include <algorithm>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-levels-3-and-4-c4244?view=msvc-160
#pragma warning( disable : 4244 )

struct hsv {
	float h{ }, s{ }, v{ };

	
};

struct color {
	unsigned char r, g, b, a;

	// ctors
	color( ) : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } { };

	color( unsigned char re, unsigned char gr, unsigned char bl, unsigned char al = 255 ) : r{ re }, g{ gr }, b{ bl }, a{ al } { };

	color( std::uint32_t hex ) : r( ( hex >> 24 ) & 0xFF ), g( ( hex >> 16 ) & 0xFF ), b( ( hex >> 8 ) & 0xFF ), a( hex & 0xFF ){ };

	constexpr static auto MAX_ALPHA = ( unsigned char )255;

	std::uint32_t to_u32( ) const
	{
		return ( ( r & 0xff ) << 24 ) + ( ( g & 0xff ) << 16 ) + ( ( b & 0xff ) << 8 ) + ( a & 0xff );
	}
	color from_u32( unsigned int col )
	{
		return color( static_cast< int >( ( col >> 0 ) & 0xFF ), static_cast< int >( ( col >> 8 ) & 0xFF ),
		              static_cast< int >( ( col >> 16 ) & 0xFF ), static_cast< int >( ( col >> 24 ) & 0xFF ) );
	}
	color set_alpha( int new_alpha )
	{
		return color( r, g, b, static_cast< unsigned char >( new_alpha ) );
	}
	D3DCOLOR to_d3d( ) const
	{
		return D3DCOLOR_ARGB( a, r, g, b );
	}
	color lerp( const color col, const float t )
	{
		constexpr auto lerp = []( const unsigned char from, const unsigned char to, const float t ) {
			return ( unsigned char )( ( 1.f - t ) * from + t * to );
		};

		color lerped = *this;

		lerped.r = lerp( r, col.r, t );
		lerped.g = lerp( g, col.g, t );
		lerped.b = lerp( b, col.b, t );
		lerped.a = lerp( a, col.a, t );

		return lerped;
	}
	bool operator==( const color& other ) const
	{
		return other.r == r && other.g == g && other.b == b && other.a == a;
	}
	bool operator!=( const color& other ) const
	{
		return other.r != r || other.g != g || other.b != b || other.a != a;
	}
	color& operator*=( const float f )
	{
		r = static_cast< int >( r * f );
		g = static_cast< int >( g * f );
		b = static_cast< int >( b * f );
		return *this;
	}
	// color operator( )( const int al ) const
	//{
	//	return color( r, g, b, al );
	// }
	color& operator/=( const float d )
	{
		const auto float_division = 1.f / d;
		*this *= float_division;

		return *this;
	}
	color& operator*( const float coeff ) const
	{
		auto color = *this;
		return color *= coeff;
	}
	// color& operator=( color col ) const
	//{
	//	color cf{ *this };
	//	cf.r = col.r;
	//	cf.g = col.g;
	//	cf.b = col.b;
	//	return cf;
	// }
	color& operator+( color col ) const
	{
		color cf = { *this };
		cf.r += col.r;
		cf.g += col.g;
		cf.b += col.b;
		cf.a += col.a;

		return cf;
	}
	color& operator-( color col ) const
	{
		color cf = { *this };
		cf.r -= col.r;
		cf.g -= col.g;
		cf.b -= col.b;
		cf.a -= col.a;

		return cf;
	}
};
