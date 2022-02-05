#include "return_address.h"

bool __stdcall hooks::return_address::return_address_detour( LPCSTR )
{
	return true;
}
