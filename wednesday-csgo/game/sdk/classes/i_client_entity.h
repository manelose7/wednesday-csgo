#pragma once

#include <iostream>

#include "i_client_networkable.h"
#include "i_client_renderable.h"
#include "i_client_thinkable.h"
#include "i_client_unknown.h"

namespace sdk
{
	struct i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable {
		virtual void release( ) = 0;

		virtual math::vec3& get_abs_origin( ) = 0;
		virtual math::vec3& get_abs_angles( ) = 0;

		template< typename T >
		T as( )
		{
			return reinterpret_cast< T >( this );
		}
	};
} // namespace sdk
