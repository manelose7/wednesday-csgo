#include "movement.h"
#include "../../gui/cfg/cfg.h"

void movement::impl::pre_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;

	g_movement.bhop( );
}

void movement::impl::post_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;
}

void movement::impl::bhop( )
{
	// will return if player is noclip/ladder/fly mode
	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	// remove jump flag if player in air
	if ( !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) )
		g_ctx.cmd->buttons.remove( sdk::buttons::IN_JUMP );
}

void movement::impl::edgebug_t::run_ticks( const bool ducking )
{
	if ( !ducking ) {
		g_ctx.cmd->buttons.remove( sdk::buttons::IN_DUCK );
		g_ctx.local->flags( ).remove( sdk::flags::DUCKING );
	} else {
		g_ctx.cmd->buttons.add( sdk::buttons::IN_DUCK );
		g_ctx.local->flags( ).add( sdk::flags::DUCKING );
	}
	// copy current local/cmd pointer to backup
	std::memcpy( m_backup.local, g_ctx.local, 0x3870 );
	std::memcpy( m_backup.cmd, g_ctx.cmd, sizeof( sdk::c_user_cmd ) );

	// loop through ticks
	for ( int m_tick = 0; m_tick <= g_cfg.get< int >( HASH( "eb_ticks" ) ); m_tick++ ) { }

	// set current pointers to backed up pointers
	std::memcpy( g_ctx.local, m_backup.local, 0x3870 );
	std::memcpy( g_ctx.cmd, m_backup.cmd, sizeof( sdk::c_user_cmd ) );
}

void movement::impl::edgebug_t::think( )
{
	// TODO: put cfg here
	if ( false )
		return;

	static int m_old_buttons = g_ctx.cmd->buttons;
}
