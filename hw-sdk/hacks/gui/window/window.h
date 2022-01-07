#pragma once
#include "../../../game/sdk/classes/i_global_vars.h"
#include "../../../game/sdk/structs/color.h"
#include "../../../globals/interfaces/interfaces.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../../utils/renderer/renderer.h"
#include "../includes/includes.h"
#include <stack>

namespace gui::tabs
{
	enum tab_index : int
	{
		AIMBOT = 0,
		VISUALS,
		MISC,
		SKINS,
		DEMOS,
		CONFIG
	};

	struct impl {
		void invoke_tabs( const std::vector< std::string_view > );

		void think( );

		int current_tab = 0;
	};
} // namespace gui::tabs

inline gui::tabs::impl g_tabs;

namespace gui::elements
{
	struct window_impl {
	public:
		window_impl( ) = default;
		explicit window_impl( std::uint8_t vk_key ) : open_key( vk_key ){ };

		bool invoke_window( const std::string_view name );
		void end_window( );

		void invoke_tab( const std::string_view name );

	private:
		struct util_t {
			void draw_background( );
			void draw_title_header( );

			void handle_drag( bool hover, const math::vec2< int >& delta );
			void handle_resize( bool hover );
		} utils;

		float ui_anim_state        = 0.f;
		bool moveable_area_hovered = false;
		bool resize_area_hovered   = false;
		std::uint8_t open_key{ };
	};

} // namespace gui::elements

inline gui::elements::window_impl g_window{ gui::elements::window_impl( VK_INSERT ) };
