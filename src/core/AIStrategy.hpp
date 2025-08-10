#ifndef AISTRATEGY_HPP
#define AISTRATEGY_HPP

// -> forward declaration para evitar importacion circular
class Enemy;
class Player;

class AIStrategy
{
    public:
        virtual ~AIStrategy() = default;
        virtual void update(Enemy& owner, Player& player) = 0;
};



#endif
