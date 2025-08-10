#ifndef PATROLLING_STRATEGY_HPP
#define PATROLLING_STRATEGY_HPP

#include "raylib.h"

#include "AIStrategy.hpp"

class PatrollingStrategy : public AIStrategy
{
    private:
        float m_patrol_timer;
        Vector2 m_patrol_direction;

    public:
        PatrollingStrategy();
        ~PatrollingStrategy() = default;
        void update(Enemy& owner, Player& player) override;
};













#endif
