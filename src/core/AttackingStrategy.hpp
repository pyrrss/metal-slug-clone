#ifndef ATTACKING_STRATEGY_HPP
#define ATTACKING_STRATEGY_HPP

#include "AIStrategy.hpp"

class AttackingStrategy : public AIStrategy
{
    public:
        AttackingStrategy();
        ~AttackingStrategy() = default;

        void update(Enemy& owner, Player& player) override;
};







#endif
