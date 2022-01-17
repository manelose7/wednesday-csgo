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
	object.m_box.m_draw         = true;

	object.m_box.m_color = color( 255, 255, 255, 255 );

	object.m_box.m_titles.clear( );
	object.m_box.m_texts.clear( );
	object.m_box.m_bars.clear( );

	auto buffer_title = esp_text( );
	// auto buffer_bar   = esp_bar( );

	buffer_title.m_location = esp_location::LOCATION_TOP;
	buffer_title.m_text     = object.m_owner->name( );
	buffer_title.m_color    = color( 255, 255, 255, 255 );
	buffer_title.m_font     = g_fonts[ HASH( "esp_font" ) ];
	buffer_title.m_flags    = font_flags::FLAG_DROPSHADOW;

	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );

	buffer_title.m_location = esp_location::LOCATION_BOTTOM;

	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );

	buffer_title.m_location = esp_location::LOCATION_LEFT;

	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );

	buffer_title.m_location = esp_location::LOCATION_RIGHT;

	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );
	object.m_box.m_texts.push_back( buffer_title );

	// buffer_bar.m_location   = esp_location::LOCATION_LEFT;
	// buffer_bar.m_width      = 2;
	// buffer_bar.m_color_from = color( 0, 255, 0, 255 );
	// buffer_bar.m_color_to   = color( 255, 0, 0, 255 );
	// buffer_bar.m_min        = 0;
	// buffer_bar.m_max        = 100;
	// buffer_bar.m_cur        = object.m_owner->health( );

	// object.m_box.m_bars.push_back( buffer_bar );
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

		auto w2s = utils::world_to_screen( player->hitbox_position( sdk::HITGROUP_HEAD ) );

		g_render.render_filled_rectangle( w2s - math::vec2( 3, 3 ), math::vec2( 6, 6 ), color( 255, 255, 255 ) );
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

	float offset_x[ 4 ]{ };
	float offset_y[ 4 ]{ };

	for ( auto& title : m_titles )
		title.render( dimensions, offset_x[ static_cast< unsigned int >( title.m_location ) ],
		              offset_y[ static_cast< unsigned int >( title.m_location ) ] );

	for ( auto& text : m_texts )
		text.render( dimensions, offset_x[ static_cast< unsigned int >( text.m_location ) ],
		             offset_y[ static_cast< unsigned int >( text.m_location ) ] );

	for ( auto& bar : m_bars )
		bar.render( dimensions, offset_x[ static_cast< unsigned int >( bar.m_location ) ],
		            offset_y[ static_cast< unsigned int >( bar.m_location ) ] );
}

void visuals::esp_title::render( math::box box, float& offset_x, float& offset_y )
{
	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), m_font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	switch ( m_location ) {
	case esp_location::LOCATION_TOP:
		break;
	case esp_location::LOCATION_LEFT:
		break;
	case esp_location::LOCATION_BOTTOM:
		break;
	case esp_location::LOCATION_RIGHT:
		break;
	}

	g_render.render_filled_rectangle( position, math::vec2< int >( text_size.x + 5, text_size.y + 4 ), color( 0, 0, 0, m_color.a * 0.7 ) );
	g_render.render_filled_rectangle( position, math::vec2< int >( 1, text_size.y + 4 ), m_color );

	g_render.render_text( position + math::vec2< int >( 3, 2 ), font_alignment::AL_DEFAULT, m_flags, m_text.c_str( ), m_font,
	                      color( 255, 255, 255, 255 ) );
}

void visuals::esp_text::render( math::box box, float& offset_x, float& offset_y )
{
	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), m_font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	switch ( m_location ) {
	case esp_location::LOCATION_TOP:
		position.x = ( box.x + box.width( ).x / 2 ) - text_size.x / 2;
		position.y = ( box.y - text_size.y ) - 1;

		position.x += offset_x;
		position.y -= offset_y;
		break;
	case esp_location::LOCATION_BOTTOM:
		position.x = ( box.x + box.width( ).x / 2 ) - text_size.x / 2;
		position.y = box.h + 1;

		position.x += offset_x;
		position.y += offset_y;
		break;
	case esp_location::LOCATION_LEFT:
		position.x = (box.x - text_size.x) - 3;
		position.y = box.y;

		position.x += offset_x;
		position.y += offset_y;
		break;
	case esp_location::LOCATION_RIGHT:
		position.x = box.w + 2;
		position.y = box.y;

		position.x += offset_x;
		position.y += offset_y;
		break;
	}

	offset_y += text_size.y;

	g_render.render_text( position, font_alignment::AL_DEFAULT, m_flags, m_text.c_str( ), m_font, m_color );
}

void visuals::esp_bar::render( math::box box, float& offset_x, float& offset_y )
{
	math::vec2< int > border_start_position;
	math::vec2< int > border_end_position;

	math::vec2< int > start_position;
	math::vec2< int > end_position;

	auto current_percentage = -( m_cur / ( m_max - m_min ) ) + 1.f;
	auto current_color      = m_color_from.lerp( m_color_to, current_percentage );

	switch ( m_location ) {
	case esp_location::LOCATION_TOP:
		break;
	case esp_location::LOCATION_LEFT:
		break;
	case esp_location::LOCATION_BOTTOM:
		break;
	case esp_location::LOCATION_RIGHT:
		break;
	}

	g_render.render_filled_rectangle( border_start_position - math::vec2< int >( 1, 1 ), border_end_position + math::vec2< int >( 2, 2 ),
	                                  color( 32, 32, 32, current_color.a - 155 ) );
	g_render.render_filled_rectangle( start_position, end_position, current_color );
}
