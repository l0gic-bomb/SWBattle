#include "GameUnit.hpp"
#include "IO/EventLogs/UnitDied.hpp"
#include "IO/EventLogs/UnitMoved.hpp"
#include "IO/EventLogs/UnitAttacked.hpp"

#include <utility>
#include <cmath>

sw::game::GameUnit::GameUnit(UnitData unitData)
        : unitData(std::move(unitData))
{
}

uint32_t sw::game::GameUnit::getId() const noexcept {
    return unitData.unitId;
}

void sw::game::GameUnit::move(uint32_t targetX, uint32_t targetY) {
    unitData.position = {targetX,targetY};
    eventListener->log(io::UnitMoved{ unitData.unitId, targetX, targetY });
}

void sw::game::GameUnit::setEventListener(const std::shared_ptr<EventLog>& listener) {
    eventListener = listener;
}

void sw::game::GameUnit::makeDamage(int enemyDamage) noexcept {
    unitData.hp -= enemyDamage;
    if (unitData.hp <= 0 ) {
        unitData.hp = 0;
        eventListener->log(io::UnitDied{ unitData.unitId });
    }
}

const std::pair<uint32_t, uint32_t>& sw::game::GameUnit::getPosition() const noexcept {
    return unitData.position;
}

bool sw::game::GameUnit::canAttack(uint32_t x, uint32_t y) {
    int distanceX = std::abs(static_cast<int>(unitData.position.first - x));
    int distanceY = std::abs(static_cast<int>(unitData.position.second - y));
    int hypotenuse = 0;
    if ((distanceX == 0 || distanceY == 0) && distanceX + distanceY <= unitData.maxRange)
    {
        enemyAndDistance.second = distanceX + distanceY;
        return true;
    }
    else if (hypotenuse = sqrt(float(distanceX * distanceX + distanceY * distanceY)); hypotenuse <= unitData.maxRange)
    {
        enemyAndDistance.second = hypotenuse;
        return true;
    }
    return false;
}

void sw::game::GameUnit::attack(const std::shared_ptr<GameUnit>& nearestEnemy) {
    if (nearestEnemy)
        enemyAndDistance.first = nearestEnemy;
    auto enemy = enemyAndDistance.first;
    if (!enemy.expired()) {
        if (enemy.lock()->isDead()) {
            enemy.reset();
            return;
        }
        eventListener->log( io::UnitAttacked{ unitData.unitId, enemy.lock()->getId(), static_cast<uint32_t>(damage), enemy.lock()->getHp() });
        enemy.lock()->makeDamage(damage);
    }
}

bool sw::game::GameUnit::hasEnemy() const noexcept {
    return (enemyAndDistance.first.lock() != nullptr);
}

bool sw::game::GameUnit::isDead() const noexcept {
    return unitData.hp == 0;
}

uint32_t sw::game::GameUnit::getHp() const noexcept {
    return unitData.hp;
}

sw::game::Warrior::Warrior(sw::game::UnitData unitData, int strength)
    : sw::game::GameUnit(unitData), strength(strength)
{
}

void sw::game::Warrior::setDamageByDistance() noexcept {
    damage = strength;
}

sw::game::Archer::Archer(sw::game::UnitData unitData, int strength, int agility)
    : sw::game::GameUnit(unitData), strength(strength), agility(agility)
{
}

void sw::game::Archer::setDamageByDistance() noexcept {
    if (enemyAndDistance.second >= 2 && enemyAndDistance.second <= unitData.maxRange)
        damage = agility;
    else
        damage = strength;
}
