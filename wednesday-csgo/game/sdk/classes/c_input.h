#pragma once

#include "../../../globals/macros/macros.h"
#include "../../../utils/math/types/vector.h"
#include "../../../utils/vfunc/vfunc.h"
#include "c_usercmd.h"
#include "c_verified_cmd.h"

#include <iostream>

constexpr std::size_t multiplayer_backup = 150;

namespace sdk
{
	class c_input
	{
	public:
		PAD( 0xC );
		bool trackir_available;
		bool mouse_initiated;
		bool mouse_active;
		bool joystick_advanced_init;
		PAD( 0x2C );
		void* keys;
		PAD( 0x6C );
		bool camera_intercepting_mouse;
		bool camera_in_third_person;
		bool camera_moving_with_mouse;
		math::vec3 camer_offset;
		bool camera_distance_move;
		int camera_old_x;
		int camera_old_y;
		int camera_x;
		int camera_y;
		bool camera_is_orthographic;
		math::vec3 previous_view_angles;
		math::vec3 preview_view_angles_tilt;
		float last_forward_move;
		int clear_input_state;
		PAD( 0x18 );
		sdk::c_user_cmd* commands;
		sdk::c_verified_cmd* verified_commands;

		inline sdk::c_user_cmd* get_user_cmd( int slot, int sequence_number );
		inline sdk::c_verified_cmd* get_verified_cmd( int sequence_number );
	};
} // namespace sdk

sdk::c_user_cmd* sdk::c_input::get_user_cmd( int slot, int sequence_number )
{
	return reinterpret_cast< sdk::c_user_cmd*( __thiscall* )( void*, int, int ) >( virtual_func::get( this, 8 ) )( this, slot, sequence_number );
}

sdk::c_verified_cmd* sdk::c_input::get_verified_cmd( int sequence_number )
{
	auto verified_commands = *reinterpret_cast< sdk::c_verified_cmd** >( reinterpret_cast< std::uint32_t >( this ) + 0xF8 );

	return &verified_commands[ sequence_number % multiplayer_backup ];
}
