#include "visuals.h"
#include "../../../globals/ctx/ctx.h"
#include <comdef.h>

math::box visuals::esp_box::calculate_box( sdk::c_cs_player* player, bool& on_screen )
{
	auto& player_info = g_entity_list.players[ player->entity_index( ) ];

	math::vec3 mins = player_info.m_mins;
	math::vec3 maxs = player_info.m_maxs;

	math::matrix_3x4 transform = player_info.m_rgfl;

	math::vec3 points[] = { math::vec3( mins.x, mins.y, mins.z ), math::vec3( mins.x, maxs.y, mins.z ), math::vec3( maxs.x, maxs.y, mins.z ),
		                    math::vec3( maxs.x, mins.y, mins.z ), math::vec3( maxs.x, maxs.y, maxs.z ), math::vec3( mins.x, maxs.y, maxs.z ),
		                    math::vec3( mins.x, mins.y, maxs.z ), math::vec3( maxs.x, mins.y, maxs.z ) };

	math::vec3 translated_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ )
		translated_points[ iterator ] = math::vector_transform( points[ iterator ], transform );

	math::vec2< int > screen_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ ) {
		bool buffer_on_screen = true;

		auto& screen_point = screen_points[ iterator ];

		screen_point = utils::world_to_screen( translated_points[ iterator ], buffer_on_screen );

		if ( buffer_on_screen && !( screen_point.x < 0 ) && !( screen_point.y < 0 ) && !( screen_point.x > g_ctx.screen_size.x ) &&
		     !( screen_point.y > g_ctx.screen_size.y ) )
			on_screen = true;
	}

	float top    = screen_points[ 0 ].y;
	float left   = screen_points[ 0 ].x;
	float right  = screen_points[ 0 ].x;
	float bottom = screen_points[ 0 ].y;

	for ( int iterator = 1; iterator < 8; iterator++ ) {
		if ( left > screen_points[ iterator ].x )
			left = screen_points[ iterator ].x;
		if ( top > screen_points[ iterator ].y )
			top = screen_points[ iterator ].y;
		if ( right < screen_points[ iterator ].x )
			right = screen_points[ iterator ].x;
		if ( bottom < screen_points[ iterator ].y )
			bottom = screen_points[ iterator ].y;
	}

	return math::box( ROUND_UP( left ), ROUND_UP( top ), ROUND_UP( right ), ROUND_UP( bottom ) );
}

void visuals::impl::update_object( esp_object& object )
{
	object.m_box.m_cornered     = false;
	object.m_box.m_outline[ 0 ] = true;
	object.m_box.m_outline[ 1 ] = true;
	object.m_box.m_draw         = false;

	object.m_box.m_color.r = 255;
	object.m_box.m_color.g = 255;
	object.m_box.m_color.b = 255;
	object.m_box.m_color.a = 255;

	object.m_box.m_titles.clear( );
	object.m_box.m_texts.clear( );

	auto buffer_title = esp_title( );
	auto buffer_text  = esp_text( );

	buffer_title.m_location = esp_location::LOCATION_LEFT;
	buffer_title.m_text     = object.m_owner->name( );
	buffer_title.m_color.r  = 200;
	buffer_title.m_color.g  = 50;
	buffer_title.m_color.b  = 0;
	buffer_title.m_color.a  = 255;
	buffer_title.m_font     = g_fonts[ HASH( "esp_font" ) ];
	buffer_title.m_flags    = font_flags::FLAG_NONE;

	object.m_box.m_titles.push_back( buffer_title );
	object.m_box.m_titles.push_back( buffer_title );

	buffer_title.m_location = esp_location::LOCATION_RIGHT;

	object.m_box.m_titles.push_back( buffer_title );
	object.m_box.m_titles.push_back( buffer_title );

	buffer_title.m_location = esp_location::LOCATION_TOP;

	object.m_box.m_titles.push_back( buffer_title );
	object.m_box.m_titles.push_back( buffer_title );
	buffer_title.m_location = esp_location::LOCATION_BOTTOM;

	object.m_box.m_titles.push_back( buffer_title );
	object.m_box.m_titles.push_back( buffer_title );

	buffer_text.m_location = esp_location::LOCATION_LEFT;
	buffer_text.m_text     = object.m_owner->name( );
	buffer_text.m_color.r  = 255;
	buffer_text.m_color.g  = 192;
	buffer_text.m_color.b  = 203;
	buffer_text.m_color.a  = 255;
	buffer_text.m_font     = g_fonts[ HASH( "esp_font" ) ];
	buffer_text.m_flags    = font_flags::FLAG_DROPSHADOW;

	object.m_box.m_texts.push_back( buffer_text );
	object.m_box.m_texts.push_back( buffer_text );

	buffer_text.m_location = esp_location::LOCATION_RIGHT;

	object.m_box.m_texts.push_back( buffer_text );
	object.m_box.m_texts.push_back( buffer_text );

	buffer_text.m_location = esp_location::LOCATION_TOP;

	object.m_box.m_texts.push_back( buffer_text );
	object.m_box.m_texts.push_back( buffer_text );
	buffer_text.m_location = esp_location::LOCATION_BOTTOM;

	object.m_box.m_texts.push_back( buffer_text );
	object.m_box.m_texts.push_back( buffer_text );
}

void visuals::impl::update( )
{
	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

		if ( !player_info.m_valid || !player )
			continue;

		esp_object& buffer_object = esp_objects[ player->entity_index( ) ];

		buffer_object.m_owner = player;

		if ( true )
			update_object( buffer_object );
	}
}

void visuals::impl::render( )
{
	update( );

	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

		if ( !player_info.m_valid || !player )
			continue;

		esp_object& object = esp_objects[ player->entity_index( ) ];

		object.m_box.render( player );
	}
}

void visuals::esp_box::render( sdk::c_cs_player* owner )
{
	bool on_screen  = false;
	auto dimensions = calculate_box( owner, on_screen );
	auto position   = math::vec2< int >( static_cast< int >( dimensions.x ), static_cast< int >( dimensions.y ) );
	auto size       = math::vec2< int >( static_cast< int >( dimensions.w ), static_cast< int >( dimensions.h ) ) - position;

	if ( !on_screen )
		return;

	if ( m_draw ) {
		// outer outline
		if ( m_outline[ 0 ] )
			g_render.render_rectangle< int >( position - math::vec2< int >( 1, 1 ), size + math::vec2< int >( 2, 2 ), color( 0, 0, 0, m_color.a ) );
		// inner outline
		if ( m_outline[ 1 ] )
			g_render.render_rectangle< int >( position + math::vec2< int >( 1, 1 ), size - math::vec2< int >( 2, 2 ), color( 0, 0, 0, m_color.a ) );

		g_render.render_rectangle< int >( position, size, m_color );
	}

	unsigned int iterator[ 4 ]{ };

	for ( auto& title : m_titles ) {
		title.render( dimensions, iterator[ static_cast< unsigned int >( title.m_location ) ] );

		iterator[ static_cast< unsigned int >( title.m_location ) ]++;
	}

	for ( auto& text : m_texts ) {
		text.render( dimensions, iterator[ static_cast< unsigned int >( text.m_location ) ] );

		iterator[ static_cast< unsigned int >( text.m_location ) ]++;
	}
}

void visuals::esp_title::render( math::box box, int offset )
{
	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), m_font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	if ( m_location == esp_location::LOCATION_TOP )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.y - text_size.y ) - ( ( text_size.y + 4 ) * offset ) ) - 6 );
	if ( m_location == esp_location::LOCATION_BOTTOM )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.h + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 10 );
	if ( m_location == esp_location::LOCATION_RIGHT )
		position = math::vec2< int >( box.w + 3, ( ( box.y + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 13 );
	if ( m_location == esp_location::LOCATION_LEFT )
		position = math::vec2< int >( ( box.x - text_size.x ) - 7, ( ( box.y + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 13 );

	g_render.render_filled_rectangle( position, math::vec2< int >( text_size.x + 5, text_size.y + 4 ), color( 0, 0, 0, m_color.a * 0.7 ) );
	g_render.render_filled_rectangle( position, math::vec2< int >( 1, text_size.y + 4 ), m_color );

	g_render.render_text( position + math::vec2< int >( 3, 2 ), font_alignment::AL_DEFAULT, m_flags, m_text.c_str( ), m_font,
	                      color( 255, 255, 255, 255 ) );
}

void visuals::esp_text::render( math::box box, int offset )
{
	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), m_font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	if ( m_location == esp_location::LOCATION_TOP )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.y - text_size.y ) - ( ( text_size.y + 4 ) * offset ) ) - 6 );
	if ( m_location == esp_location::LOCATION_BOTTOM )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.h + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 10 );
	if ( m_location == esp_location::LOCATION_RIGHT )
		position = math::vec2< int >( box.w + 2, ( ( box.y + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 10 );
	if ( m_location == esp_location::LOCATION_LEFT )
		position = math::vec2< int >( ( box.x - text_size.x ) - 1, ( ( box.y + text_size.y ) + ( ( text_size.y + 4 ) * offset ) ) - 10 );

	g_render.render_text( position, font_alignment::AL_DEFAULT, m_flags, m_text.c_str( ), m_font, m_color );
}

void visuals::esp_bar::render( math::box box, int offset )
{
	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), m_font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > start_position;
	math::vec2< int > end_position;

	if ( m_location == esp_location::LOCATION_TOP ) {
		start_position = math::vec2< int >( box.x, box.y - m_width - 4 );
		end_position   = math::vec2< int >( box.w, box.y );
	}
	if ( m_location == esp_location::LOCATION_BOTTOM ) {
		start_position = math::vec2< int >( box.x, box.h );
		end_position   = math::vec2< int >( box.w, box.h + m_width + 4 );
	}
	if ( m_location == esp_location::LOCATION_RIGHT ) {
		start_position = math::vec2< int >( box.w, box.y );
		end_position   = math::vec2< int >( box.w + m_width + 4, box.h );
	}
	if ( m_location == esp_location::LOCATION_LEFT ) {
		start_position = math::vec2< int >( box.x - m_width - 4, box.y );
		end_position   = math::vec2< int >( box.x, box.h );
	}
}
