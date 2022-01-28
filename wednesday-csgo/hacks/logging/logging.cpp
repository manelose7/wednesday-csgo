#include "logging.h"
#include "../../game/sdk/structs/color.h"
#include "../../globals/interfaces/interfaces.h"
#include "../../utils/renderer/renderer.h"

void logging::impl::print( std::string_view text, std::string_view prefix, float time )
{
	logs.push_back( logging::log_text_t( text, prefix, time ) );
}

void logging::impl::think( )
{
	int x = 10, y = 5, size = 15;
	color draw_color = color( 255, 255, 255, 255 );
	float left{ };

	for ( std::size_t i = 0U; i < logs.size( ); i++ ) {
		auto& log = logs[ i ];

		log.m_time -= g_interfaces.globals->frame_time;
		if ( log.m_time <= 0.f || i > 15 ) {
			logs.erase( logs.begin( ) + i );
			continue;
		}
	}

	if ( logs.empty( ) )
		return;

	for ( std::size_t i = 0U; i < logs.size( ); i++ ) {
		auto& log = logs[ i ];
		left      = log.m_time;

		if ( left < 0.5f ) {
			float f = left;
			f       = std::clamp( f, 0.f, .5f );

			f /= .5f;

			draw_color.a = ( int )( f * 255.f );

			if ( i == 0 && f < 0.2f )
				y -= size * ( 1.f - f / 0.2f );
		} else
			draw_color.a = 255;

		g_render.render_text( x, y, font_alignment::AL_DEFAULT, font_flags::FLAG_DROPSHADOW, log.m_prefix.data( ),
		                      g_fonts[ HASH( "main_font_bold" ) ], color( 255, 255, 255, 255 ) );

		g_render.render_text( x + 3 + g_render.render_text_size( log.m_text.data( ), g_fonts[ HASH( "main_font" ) ] ).x, y,
		                      font_alignment::AL_DEFAULT, font_flags::FLAG_DROPSHADOW, log.m_text.data( ), g_fonts[ HASH( "main_font" ) ],
		                      draw_color );
		y += size;
	}
}
