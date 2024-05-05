#pragma once

#include "GameMap.hpp"
#include "GameUnit.hpp"

#include <cmath>
#include <vector>
#include <algorithm>

namespace sw::game {
    static constexpr int STEP = 8;

    //! Вспомогательная функция для вычисления расстояния между двумя точками
    double distance(int x1, int y1, int x2, int y2) {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    //! Функция поиска пути перебором для врага
    std::pair<int, int> findMove(int x, int y, int targetX, int targetY) {
        double minDistance = distance(x, y, targetX, targetY);

        if (minDistance < STEP)
            return {targetX + 1, targetY};

        int moveX = x;
        int moveY = y;

        for (int stepX = -STEP; stepX <= STEP; ++stepX) {
            for (int stepY = -STEP; stepY <= STEP; ++stepY) {
                    double d = distance(x + stepX, y + stepY, targetX, targetY);
                    if (d < minDistance) {
                        minDistance = d;
                        moveX = x + stepX;
                        moveY = y + stepY;
                    }
            }
        }

        return {moveX, moveY};
    }

    //! Поиска позиции врага на карте
    std::pair<int, int> searchPositionEnemy(const std::vector<std::vector<bool>>& map,
                                            std::pair<int, int> point,
                                            std::vector<std::vector<bool>>& visited,
                                            const std::pair<int, int>& initPoint,
                                            bool leftTop = true)
    {
        if (map[point.first][point.second]) {
            if (point != initPoint)
                return point;
        }

        const size_t ROWS = map.size();
        const size_t COLS = map[0].size();

        visited[point.first][point.second] = true;

        if (leftTop) {
            if (point.first > 0 && !visited[point.first - 1][point.second])
                return searchPositionEnemy(map, {point.first - 1, point.second}, visited, initPoint);
            if (point.second > 0 && !visited[point.first][point.second - 1])
                return searchPositionEnemy(map, {point.first, point.second - 1}, visited, initPoint);
            if (point.first < ROWS - 1 && !visited[point.first + 1][point.second])
                return searchPositionEnemy(map, {point.first + 1, point.second}, visited, initPoint);
            if (point.second < COLS - 1 && !visited[point.first][point.second + 1])
                return searchPositionEnemy(map, {point.first, point.second + 1}, visited, initPoint);
            return point;
        }
        else
        {
            if (point.first < ROWS - 1 && !visited[point.first + 1][point.second])
                return searchPositionEnemy(map, {point.first + 1, point.second}, visited, initPoint);
            if (point.second < COLS - 1 && !visited[point.first][point.second + 1])
                return searchPositionEnemy(map, {point.first, point.second + 1}, visited, initPoint);
            if (point.first > 0 && !visited[point.first - 1][point.second])
                return searchPositionEnemy(map, {point.first - 1, point.second}, visited, initPoint);
            if (point.second > 0 && !visited[point.first][point.second - 1])
                return searchPositionEnemy(map, {point.first, point.second - 1}, visited, initPoint);
            return point;
        }
    }

    //! Поиска ближайшего врага к позициии positionUnit
    std::shared_ptr<GameUnit> getNearestEnemy(GameMap* map, const std::pair<uint32_t, uint32_t>& positionUnit)
    {
        std::vector<std::vector<bool>> visited(map->getFilledMap().size(), std::vector<bool>(map->getFilledMap()[0].size(), false));
        auto pos = searchPositionEnemy(map->getFilledMap(), positionUnit, visited, positionUnit);
        if (!map->getFilledMap()[pos.first][pos.second])
        {
            pos = searchPositionEnemy(map->getFilledMap(), positionUnit, visited, positionUnit, false);
            if (!map->getFilledMap()[pos.first][pos.second])
                return nullptr;
        }
        auto nearestEnemy = map->getUnitByPosition(pos);
        return nearestEnemy;
    }

    //! Симуляция боя
    void simulateBattle(GameMap* map, std::shared_ptr<GameUnit>& unit)
    {
        auto nearestEnemy = getNearestEnemy(map, unit->getPosition());
        if (unit->canAttack(nearestEnemy->getPosition().first, nearestEnemy->getPosition().second)) {
            unit->setDamageByDistance();
            unit->attack(nearestEnemy);
        }
        else {
            auto nextPosition = findMove(static_cast<int>(unit->getPosition().first),
                                         static_cast<int>(unit->getPosition().second),
                                         static_cast<int>(nearestEnemy->getPosition().first),
                                         static_cast<int>(nearestEnemy->getPosition().second));
            map->marchOnMap(unit->getId(), nextPosition.first, nextPosition.second);
        }
    }




}
