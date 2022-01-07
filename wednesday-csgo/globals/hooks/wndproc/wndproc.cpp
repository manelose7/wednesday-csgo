#include "wndproc.h"
#include "../../../game/sdk/structs/cnetmsg_signonstate_t.h"
#include "../../../utils/modules/modules.h"

HRESULT WINAPI hooks::wndproc::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( message, parameter, long_parameter );

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	return lazy_callwndproc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
