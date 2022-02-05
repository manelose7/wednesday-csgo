#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../game/sdk/structs/renderable_info.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../interfaces/interfaces.h"
#include "../hooking.h"

namespace hooks
{
	CREATE_HOOK_HELPER( return_address_hook_client, bool( __stdcall )( LPCSTR ) );
	CREATE_HOOK_HELPER( return_address_hook_engine, bool( __stdcall )( LPCSTR ) );
	CREATE_HOOK_HELPER( return_address_hook_studio, bool( __stdcall )( LPCSTR ) );
	CREATE_HOOK_HELPER( return_address_hook_material, bool( __stdcall )( LPCSTR ) );

	struct return_address {
		static bool __stdcall return_address_detour( LPCSTR );

		static void init( )
		{
			hooks::return_address_hook_client.create( g_client_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                          return_address_detour, _( "return_address_detour" ) );
			hooks::return_address_hook_engine.create( g_engine_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                          return_address_detour, _( "return_address_detour" ) );
			hooks::return_address_hook_studio.create( g_studio_render_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                          return_address_detour, _( "return_address_detour" ) );
			hooks::return_address_hook_material.create( g_material_system_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                            return_address_detour, _( "return_address_detour" ) );
		}

		static void unload( )
		{
			hooks::return_address_hook_client.disable( );
			hooks::return_address_hook_engine.disable( );
			hooks::return_address_hook_studio.disable( );
			hooks::return_address_hook_material.disable( );
		}
	};
} // namespace hooks
