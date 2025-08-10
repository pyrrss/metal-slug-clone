#include <iostream>

#include "AttackingStrategy.hpp"

#include "../entities/Enemy.hpp"
#include "../entities/Player.hpp"

AttackingStrategy::AttackingStrategy()
{

}

void AttackingStrategy::update(Enemy& owner, Player& player)
{
    std::cout << "LOG: Enemy Attacking Strategy" << std::endl;
    

    owner.attack();
}
