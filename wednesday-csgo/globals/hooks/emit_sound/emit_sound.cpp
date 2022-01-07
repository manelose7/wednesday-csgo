#include "emit_sound.h"
#include "../../ctx/ctx.h"
#include <type_traits>

void __fastcall hooks::emit_sound::emit_sound_detour( void* ecx, void* edx, void* filter, int entity_index, int channel, const char* sound_entry,
                                                      unsigned int sound_entry_hash, const char* sample, float volume, int seed, int sound_level,
                                                      int flags, int pitch, const math::vec3* origin, const math::vec3* direction,
                                                      void* utl_vec_origins, bool update_positions, float soundtime, int speaker_entity,
                                                      void* sound_params )
{
	if ( !g_ctx.local || g_interfaces.engine->connected_safe( ) )
		goto CALL_ORIGINAL;

	// dont play sounds twice while running ProcessMove
	//if ( g_interfaces.prediction->in_prediction_var && !g_interfaces.prediction->is_first_time_predicted_var )
	//	return;

	goto CALL_ORIGINAL;

CALL_ORIGINAL:
	hooks::emit_sound_hook.call_original< void >( ecx, edx, filter, entity_index, channel, sound_entry, sound_entry_hash, sample, volume, seed,
	                                              sound_level, flags, pitch, origin, direction, utl_vec_origins, update_positions, soundtime,
	                                              speaker_entity, sound_params );
}
