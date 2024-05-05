#include "GameMap.hpp"
#include "GameUnit.hpp"
#include "Simulation.hpp"
#include "IO/EventLogs/MapCreated.hpp"
#include "IO/EventLogs/MarchStarted.hpp"
#include "IO/EventLogs/MarchEnded.hpp"
#include "IO/EventLogs/UnitSpawned.hpp"

sw::game::GameMap::GameMap(uint32_t width, uint32_t height)
    : map(width, std::vector<bool>(height, false))
{
}

void sw::game::GameMap::addUnit(std::shared_ptr<GameUnit> &&unit, const std::string& name) {
    if (unit->getPosition().first < 0 || unit->getPosition().first > map.size())
        return;
    if (unit->getPosition().second < 0 || unit->getPosition().second > map[0].size())
        return;

    map[unit->getPosition().first][unit->getPosition().second] = true;
    const auto id = unit->getId();
    units[id] = std::move(unit);
    units[id]->setEventListener(eventListener);
    eventListener->log(io::UnitSpawned{ units[id]->getId(), name,
                                        units[id]->getPosition().first, units[id]->getPosition().second });
}

void sw::game::GameMap::marchOnMap(uint32_t unitId, uint32_t targetX, uint32_t targetY) {
    if (map[targetX][targetY])
        return;
    if (units.count(unitId) == 0)
        return;

    eventListener->log(io::MarchStarted{ unitId, units[unitId]->getPosition().first, units[unitId]->getPosition().second,
                                         targetX, targetY });
    map[units[unitId]->getPosition().first][units[unitId]->getPosition().second] = false;
    map[targetX][targetY] = true;
    units[unitId]->move(targetX, targetY);
    eventListener->log(io::MarchEnded{ unitId, targetX, targetY });
}

void sw::game::GameMap::update() {
    for (auto [id, unit] : units) {
        if (unit && units.size() > 1 && !unit->isDead())
        {
            if (unit->hasEnemy())
                unit->attack();
            else
                simulateBattle(this, unit);
        }
    }
    removeDeadUnits();
}

std::size_t sw::game::GameMap::getCountUnit() const noexcept {
    return units.size();
}

const std::vector<std::vector<bool>> &sw::game::GameMap::getFilledMap() const noexcept {
    return map;
}

std::shared_ptr<sw::game::GameUnit> sw::game::GameMap::getUnitByPosition(std::pair<uint32_t, uint32_t> position) const noexcept {
    for (auto& [id, unit] : units)
        if (unit->getPosition() == position)
            return unit;
    return nullptr;
}

void sw::game::GameMap::removeDeadUnits() {
    if (units.size() < 2)
        return;
    std::vector<uint32_t> ids;
    for (const auto& [id, unit] : units)
    {
        if (unit->isDead()) {
            ids.push_back(id);
            map[unit->getPosition().first][unit->getPosition().second] = false;
        }
    }
    if (ids.empty()) return;
    for (auto id : ids)
        units.erase(id);
}

void sw::game::GameMap::setEventListener(const std::shared_ptr<EventLog>& listener) {
    eventListener = listener;
}

