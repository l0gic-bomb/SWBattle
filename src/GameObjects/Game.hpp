#pragma  once

#include <fstream>
#include <queue>

#include "GameMap.hpp"
#include "GameUnit.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/Commands/Command.hpp"

namespace sw::game {
    class Game {
    public:
        void initGame(std::ifstream& fileInit);
        void update();

        void setMap(std::unique_ptr<GameMap>&& map) noexcept;
        void addUnitToMap(std::shared_ptr<GameUnit>&& unit, const std::string& name);

        void march(uint32_t id, uint32_t x, uint32_t y);
        void setDelayTime(uint32_t ticks) noexcept;

        [[nodiscard]] bool isGameFinished() const noexcept;

    private:
        std::unique_ptr<GameMap> map;
        std::shared_ptr<EventLog> eventListner;

        std::queue<std::unique_ptr<sw::io::Command>> commands;

        uint32_t delayTime {};
        bool gameFinish {false};
    };
}


