#include <iostream>

#include "Enemy.hpp"

Enemy::Enemy(Vector2 position, Vector2 size, Vector2 velocity, int health, int damage) : Entity(position, size, velocity)
{
    // se llama inmediatamente al constructor de Entity y se le pasan sus parámetros (posición, tamaño, velocidad)
    
    this->m_health = health;
    this->m_damage = damage;


}
