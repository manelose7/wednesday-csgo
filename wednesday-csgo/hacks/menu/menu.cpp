#include "menu.h"

#include "window/tab/group/objects/checkbox.h"
#include "window/tab/group/objects/slider_int.h"

#include "window/window.h"

static auto main_window = new menu::window{ };

static auto tab1 = new menu::tab{ main_window, std::string( "hi1" ) };
static auto tab2 = new menu::tab{ main_window, std::string( "hi2" ) };
static auto tab3 = new menu::tab{ main_window, std::string( "hi3" ) };
static auto tab4 = new menu::tab{ main_window, std::string( "hi4" ) };

bool menu::impl::init( )
{
	g_config.insert( _( "menu_color" ), config::option( color( 67, 0, 187 ) ) );

	g_config.insert( _( "menu_size_x" ), config::option( 400, 0, 0 ) );
	g_config.insert( _( "menu_size_y" ), config::option( 500, 0, 0 ) );

	g_config.insert( _( "buffer_value_bool_1" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_1" ), config::option( 12, 0, 100 ) );
	g_config.insert( _( "buffer_value_bool_2" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_2" ), config::option( 12, 0, 100 ) );
	g_config.insert( _( "buffer_value_bool_3" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_3" ), config::option( 12, 0, 100 ) );

	static auto group1 = new menu::group{ tab1, std::string( "group1" ), static_cast< int >( group_position::GROUP_LEFT ), false };
	static auto group2 = new menu::group{ tab1, std::string( "group2" ), static_cast< int >( group_position::GROUP_LEFT ), false };
	static auto group3 = new menu::group{ tab1, std::string( "group3" ), static_cast< int >( group_position::GROUP_RIGHT ), true };

	static auto checkbox1 = new menu::check_box{ group1, HASH( "buffer_value_bool_1" ), _( "test" ) };
	static auto slider1   = new menu::slider_int{ group1, HASH( "buffer_value_int_1" ), _( "test" ) };
	static auto checkbox2 = new menu::check_box{ group1, HASH( "buffer_value_bool_2" ), _( "test" ) };
	static auto slider2   = new menu::slider_int{ group1, HASH( "buffer_value_int_2" ), _( "test" ) };
	static auto checkbox3 = new menu::check_box{ group1, HASH( "buffer_value_bool_3" ), _( "test" ) };
	static auto slider3   = new menu::slider_int{ group1, HASH( "buffer_value_int_3" ), _( "test" ) };

	group1->objects.push_back( checkbox1 );
	group1->objects.push_back( slider1 );
	group1->objects.push_back( checkbox2 );
	group1->objects.push_back( slider2 );
	group1->objects.push_back( checkbox3 );
	group1->objects.push_back( slider3 );

	tab1->groups.push_back( group1 );
	tab1->groups.push_back( group2 );
	tab1->groups.push_back( group3 );

	main_window->tabs.push_back( tab1 );
	main_window->tabs.push_back( tab2 );
	main_window->tabs.push_back( tab3 );
	main_window->tabs.push_back( tab4 );

	g_input.add_keybind( VK_INSERT, [ & ]( bool pressed ) {
		if ( pressed )
			menu_open = !menu_open;
	} );

	return true;
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	auto menu_size_x = g_config.find< int >( _( "menu_size_x" ) );
	auto menu_size_y = g_config.find< int >( _( "menu_size_y" ) );

	static auto menu_position_x = g_ctx.screen_size.x / 2 - menu_size_x / 2;
	static auto menu_position_y = g_ctx.screen_size.y / 2 - menu_size_y / 2;

	main_window->draw( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
	main_window->input( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
}
