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

		struct edgebug_t {
			bool success;
			bool failed;
			int ticks;
			int tickcount;
			float moused_x;
			static movement::edgebug_type mode;

			struct {
				sdk::c_user_cmd* cmd    = g_ctx.backup.cmd;
				sdk::c_cs_player* local = g_ctx.backup.local;
			} m_backup;

			void think( );
			void run_ticks( const bool ducking );
		};

		struct longjump_t {
			bool standalone = false, start_timer = false;
			int timestamp;
		};

		void bhop( );
	};
} // namespace movement

inline movement::impl g_movement;
