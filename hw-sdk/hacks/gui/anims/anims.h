#pragma once
#include "../utils/utils.h"
#include <algorithm>

namespace gui
{ // too lazy too finish this now(TODO: use frametime so anims dont go crzy on high fps)
	struct animator_t {
		explicit animator_t( ) = default;
		inline ~animator_t( ){ };

		void set( bool increment, const float& in, const float& out )
		{
			anim_state += increment ? in * 0.001f : -out * 0.001f;
			anim_state = std::clamp( anim_state, 0.f, 1.f );
			anim_factor += increment ? gui::easing::in_quint( anim_state ) : gui::easing::out_quint( anim_state );
			anim_factor = std::clamp( anim_factor, 0.f, 1.f );
		}

	private:
		float anim_factor{ };
		float anim_state{ };
	};

} // namespace gui
