#include "globals/includes/includes.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	switch ( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:
		LI_FN( DisableThreadLibraryCalls )( hModule );

		return utils::cheat_create_thread( wednesday::init, hModule );
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
};
