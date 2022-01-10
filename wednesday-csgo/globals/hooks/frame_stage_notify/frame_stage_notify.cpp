#include "frame_stage_notify.h"

void __fastcall hooks::frame_stage_notify::frame_stage_notify_detour( void* self, void* ecx, sdk::frame_stage stage )
{
	hooks::frame_stage_notify_hook.call_original< void >( self, ecx, stage );

	switch ( stage ) {
		using enum sdk::frame_stage;
	case NET_UPDATE_END:
		g_entity_list.update( );

		for ( auto event = g_interfaces.client_state->events; event; event = event->next )
			event->fire_delay = 0.f;

		g_interfaces.engine->fire_events( );

		for ( auto& player_info : g_entity_list.players ) {
			auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

			if ( !player_info.m_valid || !player )
				continue;

			g_ctx.updating_animations = true;
			// player->update_client_side_animation( );
			// g_ctx.updating_animations = false;
		}

		g_lagcomp.update( );
		break;
	}
}
