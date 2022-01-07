#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "../../globals/macros/macros.h"

namespace logging
{
	struct log_text_t {
		log_text_t( ) = default;
		log_text_t( std::string_view text, std::string_view prefix, float time )
			: m_text{ std::move( text ) }, m_prefix{ std::move( prefix ) }, m_time{ time } { };

		std::string_view m_text{ }, m_prefix{ };
		float m_time{ };
	};

	class impl
	{
	public:
		impl( ) : logs{ } { };

		void print( std::string_view text, std::string_view prefix = _( "[log]" ), float time = 8.f );

		void think( );
	private:
		std::vector< logging::log_text_t > logs{ };
	};
} // namespace logging

inline logging::impl g_log;
