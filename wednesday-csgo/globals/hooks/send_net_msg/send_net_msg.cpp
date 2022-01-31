#include "send_net_msg.h"
#include "../../../utils/keybinds/keybinds.h"

bool __fastcall hooks::send_net_msg::send_net_msg_detour( void* ecx, void* edx, sdk::i_net_msg* net_message, bool reliable, bool voice )
{
	if ( net_message->get_type( ) == 14 )
		return false;

	if ( net_message->get_type( ) == 10 )
		voice = true;

	return send_net_msg_hook.call_original< bool >( ecx, edx, net_message, reliable, voice );
}
