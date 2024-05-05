#pragma once

namespace sw::game
{
    class Game;
}

namespace sw::io {
    struct Command {
        virtual ~Command() = default;
        virtual void execute(sw::game::Game* game) = 0;
    };
}

