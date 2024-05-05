#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "ObservableObject.hpp"

namespace sw::game {
    class GameUnit;
    class GameMap : public ObservableObject {
    public:
        explicit GameMap(uint32_t width, uint32_t height);

        void update();

        void marchOnMap(uint32_t unitId, uint32_t targetX, uint32_t targetY);
        void addUnit(std::shared_ptr<GameUnit> &&unit, const std::string& name);
        void removeDeadUnits();

        [[nodiscard]] std::size_t getCountUnit() const noexcept;
        [[nodiscard]] const std::vector<std::vector<bool>>& getFilledMap() const noexcept;
        [[nodiscard]] std::shared_ptr<GameUnit> getUnitByPosition(std::pair<uint32_t, uint32_t> position) const noexcept;

    private:
        std::vector<std::vector<bool>> map;
        std::unordered_map<uint32_t, std::shared_ptr<GameUnit>> units;
    };
}
