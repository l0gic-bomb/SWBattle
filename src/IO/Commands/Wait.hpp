#pragma once

#include <iosfwd>
#include <cstdint>
#include "Command.hpp"

namespace sw::io
{
    struct Wait : public Command
	{
		constexpr static const char* Name = "WAIT";

		uint32_t ticks {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("ticks", ticks);
		}

        ~Wait() override = default;

        void execute(sw::game::Game* game) override {
            game->setDelayTime(ticks);
        };
	};
}