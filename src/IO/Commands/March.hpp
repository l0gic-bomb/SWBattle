#pragma once

#include <iosfwd>
#include <cstdint>
#include "GameObjects/GameUnit.hpp"
#include "Command.hpp"

namespace sw::io
{
    struct March : public Command
	{
		constexpr static const char* Name = "MARCH";

		uint32_t unitId {};
		uint32_t targetX {};
		uint32_t targetY {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}

        ~March() override = default;

        void execute(sw::game::Game* game) override {
            game->march(unitId, targetX - 1, targetY - 1);
        }
	};
}