#include "anim_fix.h"
#include "../../ctx/ctx.h"

void __fastcall hooks::standard_blending_rules::standard_blending_rules_detour( sdk::c_cs_player* player, void* edx, void* hdr, math::vec3* position,
                                                                                math::quaternion< float >* quaternion, float curtime, int bone_mask )
{
	auto backup_effects = player->effects( );

	if ( player == g_ctx.local ) {
		player->effects( ).remove( 0x8 );

		standard_blending_rules_hook.call_original< void >( player, edx, hdr, position, quaternion, curtime, bone_mask );

		player->effects( ) = backup_effects;
	} else {
		standard_blending_rules_hook.call_original< void >( player, edx, hdr, position, quaternion, curtime, bone_mask );
	}
}

void __fastcall hooks::do_extra_bone_processing::do_extra_bone_processing_detour( sdk::c_cs_player* player, void* edx, void* hdr,
                                                                                  math::vec3* position, math::quaternion< float >* quaternion,
                                                                                  math::matrix_3x4* matrix, std::uint8_t* bone_list, void* context )
{
	return;
}

void __fastcall hooks::update_client_side_animation::update_client_side_animation_detour( sdk::c_cs_player* player, void* edx )
{
	if ( g_ctx.updating_animations )
		return update_client_side_animation_hook.call_original< void >( player, edx );

	if ( player == g_ctx.local )
		return update_client_side_animation_hook.call_original< void >( player, edx );
}

bool __fastcall hooks::should_skip_animation_frame::should_skip_animation_frame_detour( void* ecx, void* edx )
{
	return false;
}

int __cdecl hooks::process_interpolated_list::process_interpolated_list_detour( )
{
	static auto allow_extrapolation = *g_client_dll.pattern_scan( _( "A2 ? ? ? ? 8B 45 E8" ) ).add( 0x1 ).as< bool** >( );

	if ( allow_extrapolation )
		*allow_extrapolation = false;

	return process_interpolated_list_hook.call_original< int >( );
}
