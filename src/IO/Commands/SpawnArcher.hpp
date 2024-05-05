#pragma once

#include <iosfwd>
#include <cstdint>
#include "GameObjects/GameUnit.hpp"
#include "Command.hpp"


namespace sw::io
{
    struct SpawnArcher : public Command
	{
		constexpr static const char* Name = "SPAWN_ARCHER";

		uint32_t unitId {};
		uint32_t x {};
		uint32_t y {};
		int hp {};
		int strength {};
		uint32_t range {};
        int agility {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
			visitor.visit("range", range);
			visitor.visit("agility", agility);
		}

        ~SpawnArcher() override = default;

        void execute(sw::game::Game* game) override {
            sw::game::UnitData unitData(unitId, x - 1, y - 1, hp, range);
            game->addUnitToMap(std::make_shared<sw::game::Archer>(unitData, strength, agility), "Archer");
        }
	};
}