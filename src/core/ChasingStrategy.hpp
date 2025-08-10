#ifndef CHASING_STRATEGY_HPP
#define CHASING_STRATEGY_HPP

#include "AIStrategy.hpp"

class ChasingStrategy : public AIStrategy
{
    public:
        ChasingStrategy();
        ~ChasingStrategy() = default;   

        void update(Enemy& owner, Player& player) override;
};













#endif
