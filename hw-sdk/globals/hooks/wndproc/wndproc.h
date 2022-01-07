#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../utils/keybinds/keybinds.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../interfaces/interfaces.h"
#include "../hooking.h"

namespace hooks
{
	inline WNDPROC wndproc_hook;
	struct wndproc {
		static LONG WINAPI wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter );

		static void init( )
		{
			hooks::wndproc_hook = reinterpret_cast< WNDPROC >(
				LI_FN( SetWindowLongA )( FindWindowA( "Valve001", nullptr ), GWL_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_detour ) ) );
		}

		static void unload( )
		{
			LI_FN( SetWindowLongA )( wednesday::window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( hooks::wndproc_hook ) );
		}
	};
} // namespace hooks
