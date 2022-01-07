#pragma once
#include <iostream>

#include "../../../globals/includes/includes.h"
#include "../structs/weapon_data_t.h"
#include "c_base_entity.h"

namespace sdk
{
	struct c_base_combat_weapon : public c_base_entity {
	public:
		NETVAR( next_primary_attack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack" );
		NETVAR( next_secondary_attack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack" );
		NETVAR( clip_mag, std::int32_t, "CBaseCombatWeapon", "m_iClip1" );
		NETVAR( clip_reserve, std::int32_t, "CBaseCombatWeapon", "m_iPrimaryReserveAmmoCount" );
		NETVAR( view_model_index, std::int32_t, "CBaseCombatWeapon", "m_iViewModelIndex" );
		NETVAR( world_model_index, std::int32_t, "CBaseCombatWeapon", "m_iWorldModelIndex" );
		NETVAR( world_dropped_model_index, std::int32_t, "CBaseCombatWeapon", "m_iWorldDroppedModelIndex" );
		NETVAR( postpone_fire_ready_time, float, "CBaseCombatWeapon", "m_flPostponeFireReadyTime" );
		NETVAR( world_view_model, std::uintptr_t, "CBaseCombatWeapon", "m_hWeaponWorldModel" );

		[[nodiscard]] sdk::weapon_data_t* get_weapon_data( )
		{
			return virtual_func::call< sdk::weapon_data_t* >( this, 461 );
		}
	};
} // namespace sdk
