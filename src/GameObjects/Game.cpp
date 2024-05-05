#include "Game.hpp"
#include "../IO/System/CommandParser.hpp"
#include "../IO/System/PrintDebug.hpp"
#include "../IO/Commands/CreateMap.hpp"
#include "../IO/Commands/SpawnWarrior.hpp"
#include "../IO/Commands/SpawnArcher.hpp"
#include "../IO/Commands/March.hpp"
#include "../IO/Commands/Wait.hpp"

#include <IO/EventLogs/MapCreated.hpp>
#include <IO/EventLogs/UnitSpawned.hpp>
#include <IO/EventLogs/MarchStarted.hpp>
#include <IO/EventLogs/MarchEnded.hpp>
#include <IO/EventLogs/UnitMoved.hpp>
#include <IO/EventLogs/UnitDied.hpp>
#include <IO/EventLogs/UnitAttacked.hpp>

void sw::game::Game::initGame(std::ifstream& fileInit) {
    io::CommandParser parser;
    parser.add<io::CreateMap>(
            [](auto command) { printDebug(std::cout, command); }
            ).add<io::SpawnWarrior>(
            [](auto command) { printDebug(std::cout, command); }
            ).add<io::SpawnArcher>(
            [](auto command) { printDebug(std::cout, command); }
            ).add<io::March>(
            [](auto command) { printDebug(std::cout, command); }
            ).add<io::Wait>(
            [](auto command) { printDebug(std::cout, command); }
            );

    parser.parse(fileInit, commands);

    eventListner = std::make_shared<EventLog>();
    eventListner->listen<io::MapCreated>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::UnitSpawned>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::MarchStarted>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::UnitMoved>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::MarchEnded>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::UnitAttacked>([](auto& event){ printDebug(std::cout, event); });
    eventListner->listen<io::UnitDied>([](auto& event){ printDebug(std::cout, event); });
}

void sw::game::Game::setMap(std::unique_ptr<GameMap>&& newMap) noexcept
{
    map = std::move(newMap);
    map->setEventListener(eventListner);
    eventListner->log(io::MapCreated{ static_cast<uint32_t>(map->getFilledMap().size()), static_cast<uint32_t>(map->getFilledMap()[0].size()) });
}

void sw::game::Game::march(uint32_t id, uint32_t x, uint32_t y) {

    map->marchOnMap(id, x, y);
}

void sw::game::Game::setDelayTime(uint32_t ticks) noexcept {
    delayTime = ticks;
}

void sw::game::Game::addUnitToMap(std::shared_ptr<GameUnit> &&unit, const std::string& name) {
    if (map)
        map->addUnit(std::move(unit), name);
}

void sw::game::Game::update() {
    if (delayTime != 0) {
        --delayTime;
        return;
    }

    if (map) {
        map->update();
        if (commands.empty() && map->getCountUnit() <= 1)
            gameFinish = true;
    }

    if (!commands.empty())
    {
        commands.front()->execute(this);
        commands.pop();
    }
}

bool sw::game::Game::isGameFinished() const noexcept {
    return gameFinish;
}
