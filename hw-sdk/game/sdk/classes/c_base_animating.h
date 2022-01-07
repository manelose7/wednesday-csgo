#pragma once
#include <iostream>

#include "../../../globals/includes/includes.h"

#include "c_base_entity.h"

namespace sdk
{
	struct c_base_animating : public c_base_entity {
	public:
		NETVAR( hitbox_set, std::int32_t, "CBaseAnimating", "m_nHitboxSet" );
		NETVAR( cycle, float, "CBaseAnimating", "m_flCycle" );

		[[nodiscard]] std::array< float, 24 >& pose_parameter( )
		{
			static std::uintptr_t offset = netvar::get_table( _( "CBaseAnimating" ), _( "m_flPoseParameter" ) );
			return *reinterpret_cast< std::array< float, 24 >* >( reinterpret_cast< std::uintptr_t >( this ) + offset );
		}

		math::vec3 hitbox_position( int index ) 
		{

		}
	};
} // namespace sdk
