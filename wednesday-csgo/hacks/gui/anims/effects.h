#pragma once
#include "../../../globals/ctx/ctx.h"
#include "../../../utils/math/math.h"

// purpose: used for simple animations on hack

namespace vfx
{
	struct snow {
		math::vec2< int > pos;
		float time;
		float speed;
		float fall_angle;
		float fall_time;
		int size;
	};

	struct impl { // this is stolen WEHUQHUAHSUEAHUSHEUW
		template< typename anim_type = vfx::snow >
		void do_animation( )
		{
			constexpr static float degree_offset = 80.f;

			static std::vector< snow > flakes;
			static float last_time = 0.f;
			float curtime          = g_interfaces.globals->current_time;

			if ( std::abs( last_time - curtime ) > 1.f )
				flakes.clear( );

			auto num_new = math::random< int >( 0, 2 );

			for ( std::size_t i{ }; i < num_new; ++i ) {
				int rand_x     = math::random( 0, g_ctx.screen_size.x - 100 );
				int rand_ang   = math::random( -30.f, 15.f );
				int rand_size  = math::random( 1, 4 );
				int rand_speed = math::random( 1.5f, 6.f );

				vfx::snow new_flake;
				new_flake.pos       = { ( float )( rand_x ), 0.f };
				new_flake.fall_ang  = rand_ang + degree_offset;
				new_flake.fall_time = 0.f;
				new_flake.size      = rand_size;
				new_flake.speed     = rand_speed;
				new_flake.time      = curtime;

				flakes.push_back( new_flake );
			}

			for ( std::size_t i{ }; i < flakes.size( ) && !flakes.empty( ); ++i ) {
				auto* it = &flakes.at( i );

				float ang = it->fall_ang;

				float x = math::util::fast_cos( math::deg2rad( ang ) );
				float y = math::util::fast_sin( math::deg2rad( ang ) );

				float alpha = 1.f;
				if ( it->pos.y + it->size / 2 >= g_ctx.screen_size.y - 1 ) {
					if ( !it->fall_time )
						it->fall_time = curtime;

					float totaltime = it->speed / 3.f;
					float endtime   = it->fall_time + totaltime;

					float delta = ( endtime - curtime ) / totaltime;
					if ( delta < 0.f ) {
						flakes.erase( flakes.begin( ) + i );
						continue;
					}

					delta = std::clamp( delta, 0.f, 1.f );
					alpha = delta;
				} else {
					it->pos.x += x * it->speed;
					it->pos.y += y * it->speed;
				}

				for ( size_t i{ }; i <= it->size; ++i )
					draw_circle( ( float )it->pos.x, ( float )it->pos.y, i, clr_t( 255, 255, 255, alpha * 255 ) );
			}

			last_time = g_csgo.m_globals->m_curtime;
		}
	};
} // namespace vfx

inline vfx::impl g_vfx;
