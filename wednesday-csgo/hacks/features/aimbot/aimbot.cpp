#include "aimbot.h"

#include "../../../game/sdk/enums/flow.h"

#include "../../../globals/ctx/ctx.h"

#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"

#include "../lagcomp/lagcomp.h"
#include "..\..\..\utils\particle_system\particle_system.h"

sdk::c_cs_player* aimbot::impl::find_closest( )
{
	float closest_fov                = FLT_MAX;
	sdk::c_cs_player* closest_player = nullptr;

	math::vec3 local_angles = g_interfaces.engine->get_view_angles( );

	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

		if ( !player_info.m_valid || !player )
			continue;

		auto player_fov = math::get_fov( local_angles, g_ctx.local->eye_position( ), player->eye_position( ) );

		if ( player_fov < closest_fov ) {
			closest_fov    = player_fov;
			closest_player = player;
		}
	}

	return closest_player;
}

void aimbot::impl::run( )
{
	if ( !g_ctx.cmd->buttons.has( sdk::buttons::IN_ATTACK ) )
		return;

	if ( !g_ctx.local )
		return;

	auto entity = find_closest( );

	if ( !entity )
		return;

	g_lagcomp.backtrack_player( entity );
}
