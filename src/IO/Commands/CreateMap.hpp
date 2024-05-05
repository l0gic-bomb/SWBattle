#pragma once

#include <iosfwd>
#include <cstdint>
#include <memory>
#include "GameObjects/GameMap.hpp"
#include "Command.hpp"

namespace sw::io
{
	struct CreateMap : public Command {
		constexpr static const char* Name = "CREATE_MAP";

		uint32_t width {};
		uint32_t height {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}

        ~CreateMap() override = default;

        void execute(sw::game::Game* game) override {
            game->setMap(std::make_unique<sw::game::GameMap>(width, height));
        }
	};
}