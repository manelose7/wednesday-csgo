#include "keybinds.h"
#include "../../globals/hooks/wndproc/wndproc.h"
#include <windowsx.h>

void input::impl::think( UINT msg, WPARAM wparam, LPARAM lparam )
{
	std::uint8_t key_id   = 0;
	key_state_t key_state = key_state_t::KEY_UP;

	mouse.scroll_amt = 0;

	switch ( msg ) {
	case WM_KEYDOWN:
		key_id    = wparam;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_KEYUP:
		key_id    = wparam;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_LBUTTONDOWN:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_LBUTTONUP:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_LBUTTONDBLCLK:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_RBUTTONDOWN:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_RBUTTONUP:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_RBUTTONDBLCLK:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MBUTTONDOWN:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MBUTTONUP:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_MBUTTONDBLCLK:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_XBUTTONDOWN:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_XBUTTONUP:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_XBUTTONDBLCLK:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MOUSEMOVE:
		mouse.pos = math::vec2< int >( GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ) );
		break;
	case WM_MOUSEWHEEL:
		mouse.scroll_amt = -( GET_WHEEL_DELTA_WPARAM( wparam ) / ( WHEEL_DELTA / 4 ) );
		break;
	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		for ( auto& key : key_states )
			key.state = key_state_t::KEY_UP;
		break;
	default:
		break;
	}

	static auto lazy_get_tickcount = LI_FN( GetTickCount64 ).get( );

	std::uint64_t time = lazy_get_tickcount( );

	if ( key_id ) {
		if ( key_state == key_state_t::KEY_UP && key_states[ key_id ].state == key_state_t::KEY_DOWN )
			key_states[ key_id ] = { key_state_t::KEY_RELEASED, time };
		else
			key_states[ key_id ] = { key_state, time };

		for ( auto iterator = key_binds.begin( ); iterator != key_binds.end( ); iterator++ ) {
			if ( iterator->virtual_key == key_id )
				iterator->callback( key_state == key_state_t::KEY_UP ? false : key_state == key_state_t::KEY_DOWN );
		}
	}
}

void input::impl::add_keybind( std::uint8_t virtual_key, std::function< void( bool ) > callback )
{
	key_binds.push_back( { virtual_key, callback } );
}

void input::impl::remove_keybind( std::uint8_t virtual_key )
{
	for ( auto iterator = key_binds.begin( ); iterator != key_binds.end( ); iterator++ ) {
		if ( iterator->virtual_key == virtual_key )
			key_binds.erase( iterator );
	}
}
