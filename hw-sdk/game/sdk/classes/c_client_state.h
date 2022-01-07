#pragma once
#include "../../../globals/macros/macros.h"
#include "i_net_channel_info.h"
#include <cstdint>

namespace sdk
{
	class c_client_state
	{
	public:
		PAD( 0x9C );
		sdk::i_net_channel_info* channel;
		PAD( 0xD4 );
		int delta_tick;
		PAD( 0x4C54 );
		int last_outgoing_command;
		int choked_commands;
		int last_command_ack;
		int command_ack;
	};
} // namespace sdk
