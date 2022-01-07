#pragma once
#include "../../../globals/macros/macros.h"
#include "../../../utils/math/math.h"
#include <minwindef.h>

namespace sdk
{
	struct studio_bone_t {
		__forceinline const char* get_name( ) const
		{
			if ( !name_index )
				return nullptr;

			return reinterpret_cast< const char* >( this ) + name_index;
		}

		int name_index;
		int parent;
		int bone_controller[ 6 ];
		math::vec3 position;
		math::quaternion< float > quaternion;
		math::vec3 rotation;
		math::vec3 position_scale;
		math::vec3 rotation_scale;
		math::matrix_3x4 pose_to_bone;
		math::quaternion< float > quaternion_alignement;
		int flags;
		int proc_type;
		int proc_index;
		mutable int physics_bone;
		int surface_prop_index;
		int contents;
		int surface_prop;
		PAD( 0x1C );
	};

	struct studio_box_t {
		__forceinline const char* get_name( ) const
		{
			if ( !name_index )
				return nullptr;

			return reinterpret_cast< const char* >( this ) + name_index;
		}

		int bone;
		int group;
		math::vec3 mins;
		math::vec3 maxs;
		int name_index;
		math::vec3 offset_orientation;
		float radius;
		PAD( 0x10 );
	};

	struct studio_hitbox_set_t {
		__forceinline char* const get_name( ) const
		{
			return ( char* )( ( DWORD )this + name_index );
		}

		__forceinline studio_box_t* get_hitbox( int i )
		{
			if ( i > hitbox_count )
				return nullptr;

			return ( studio_box_t* )( ( DWORD )this + hitbox_index ) + i;
		}

		int name_index;
		int hitbox_count;
		int hitbox_index;
	};

	struct studio_hdr_t {
		__forceinline studio_hitbox_set_t* get_hitbox_set( int i )
		{
			if ( i < 0 || i > hitbox_sets_count )
				return nullptr;

			return ( studio_hitbox_set_t* )( ( DWORD )this + hitbox_set_index ) + i;
		}

		__forceinline studio_bone_t* get_bone( int i )
		{
			if ( i < 0 || i >= bones_count )
				return nullptr;

			return ( studio_bone_t* )( ( std::uint8_t* )this + bone_index ) + i;
		}

		int id;
		int version;
		int checksum;
		char name_char_array[ 64 ];
		int length;
		math::vec3 eye_pos;
		math::vec3 illium_pos;
		math::vec3 hull_mins;
		math::vec3 hull_maxs;
		math::vec3 mins;
		math::vec3 maxs;
		int flags;
		int bones_count;
		int bone_index;
		int bone_controllers_count;
		int bone_controller_index;
		int hitbox_sets_count;
		int hitbox_set_index;
		int local_anim_count;
		int local_anim_index;
		int local_seq_count;
		int local_seq_index;
		int activity_list_version;
		int events_indexed;
		int textures_count;
		int texture_index;
	};
} // namespace sdk
