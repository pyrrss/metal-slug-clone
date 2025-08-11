#include <iostream>

#include "PatrollingStrategy.hpp"

#include "../entities/Enemy.hpp"
#include "../entities/Player.hpp"

PatrollingStrategy::PatrollingStrategy()
{
    m_patrol_timer = 0.0f;
    m_patrol_direction = { 1, 0 };
}

void PatrollingStrategy::update(Enemy& owner, Player& player)
{
    std::cout << "LOG: Enemy Patrolling Strategy" << std::endl;

    m_patrol_timer += GetFrameTime(); 

    // -> cada ciertos segundos cambia de dirección
    if (m_patrol_timer >= GetRandomValue(1, 3))
    {
        m_patrol_timer = 0.0f;
        m_patrol_direction.x *= -1;
    }
    
    owner.move(m_patrol_direction);
    

}



