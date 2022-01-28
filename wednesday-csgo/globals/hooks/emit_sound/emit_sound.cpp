#include "emit_sound.h"
#include "../../ctx/ctx.h"
#include <type_traits>

void __fastcall hooks::emit_sound::emit_sound_detour( void* ecx, void* edx, void* filter, int entity_index, int channel, const char* sound_entry,
                                                      unsigned int sound_entry_hash, const char* sample, float volume, int seed, int sound_level,
                                                      int flags, int pitch, const math::vec3* origin, const math::vec3* direction,
                                                      void* utl_vec_origins, bool update_positions, float soundtime, int speaker_entity,
                                                      void* sound_params )
{
	emit_sound_hook.call_original< void >( ecx, edx, filter, entity_index, channel, sound_entry, sound_entry_hash, sample, volume, seed, sound_level,
	                                       flags, pitch, origin, direction, utl_vec_origins, update_positions, soundtime, speaker_entity,
	                                       sound_params );

	if ( !origin )
		return;

	auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( entity_index );

	if ( !player )
		return;

	if ( !player->is_player( ) )
		return;

	g_entity_list.players[ player->entity_index( ) ].m_dormant_info.m_last_position = *origin;
	g_entity_list.players[ player->entity_index( ) ].m_dormant_info.m_found_tick    = g_interfaces.globals->tick_count;
}
