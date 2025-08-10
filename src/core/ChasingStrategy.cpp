#include <iostream>

#include "ChasingStrategy.hpp"

#include "raylib.h"
#include "raymath.h"

#include "../entities/Enemy.hpp"
#include "../entities/Player.hpp"

ChasingStrategy::ChasingStrategy() {}

void ChasingStrategy::update(Enemy& owner, Player& player)
{
    std::cout << "LOG: Enemy Chasing Strategy" << std::endl;
    
    Vector2 owner_position = owner.get_position();
    Vector2 player_position = player.get_position();
 
    Vector2 direction = Vector2Normalize(Vector2Subtract(player_position, owner_position));
    
    owner.move(direction);
}
