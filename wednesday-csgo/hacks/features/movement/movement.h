#pragma once

#include "../../../globals/ctx/ctx.h"
#include "../../../globals/includes/includes.h"

namespace movement
{
	enum edgebug_type : int
	{
		STANDING = 0,
		DUCKING,
		ONETICK
	};

	struct impl {
		struct pre_prediction {
			void think( );
		} pre_prediction;
		struct post_prediction {
			void think( );
		} post_prediction;

		void movement_fix( sdk::c_user_cmd* command, math::vec3 old_view_angle );

		void jump_bug( );

		void mini_hop( );
		void bhop( );
	};
} // namespace movement

inline movement::impl g_movement;
