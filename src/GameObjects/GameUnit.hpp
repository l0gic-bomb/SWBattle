#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "ObservableObject.hpp"

namespace sw::game {

    struct UnitData {
        explicit UnitData(uint32_t unitId, uint32_t x, uint32_t y, uint32_t hp, uint32_t maxRange)
            : unitId(unitId), position(x, y), hp(hp), maxRange(maxRange) {}
        uint32_t unitId{};
        std::pair<uint32_t, uint32_t> position;
        int hp {};
        uint32_t maxRange {};
    };

    class GameUnit : public ObservableObject {
    public:
        explicit GameUnit(UnitData unitData);

        void move(uint32_t targetX, uint32_t targetY);

        [[nodiscard]] uint32_t getId() const noexcept;
        [[nodiscard]] const std::pair<uint32_t, uint32_t>& getPosition() const noexcept;
        [[nodiscard]] uint32_t getHp() const noexcept;
        [[nodiscard]] bool hasEnemy() const noexcept;
        [[nodiscard]] bool isDead() const noexcept;

        void attack(const std::shared_ptr<GameUnit>& nearestEnemy = nullptr);
        bool canAttack(uint32_t x, uint32_t y);
        virtual void setDamageByDistance() noexcept = 0;

        void makeDamage(int enemyDamage) noexcept;
    protected:
        UnitData unitData;
        std::pair<std::weak_ptr<GameUnit>, int> enemyAndDistance;
        int damage {};

        //std::vector<std::shared_ptr<Attack>> attacks;
        //std::shared_ptr<Attack> currentAttack;
    };

    class Warrior : public GameUnit {
    public:
        explicit Warrior(UnitData unitData, int strength);
        void setDamageByDistance() noexcept override;
    private:
        int strength {};
    };

    class Archer : public GameUnit {
    public:
        explicit Archer(UnitData unitData, int strength, int agility);
        void setDamageByDistance() noexcept override;
    private:
        int strength{};
        int agility{};
    };
}


