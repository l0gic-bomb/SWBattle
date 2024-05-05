#pragma once

#include <iosfwd>
#include <cstdint>
#include "Command.hpp"

namespace sw::io
{
    struct SpawnWarrior : public Command
	{
		constexpr static const char* Name = "SPAWN_WARRIOR";

		uint32_t unitId {};
		uint32_t x {};
		uint32_t y {};
		int hp {};
		int strength {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}

        ~SpawnWarrior() override = default;

        void execute(sw::game::Game* game) override {
            sw::game::UnitData unitData(unitId, x - 1, y - 1, hp, 1);
            game->addUnitToMap(std::make_shared<sw::game::Warrior>(unitData, strength), "Warrior");
        }
	};
}