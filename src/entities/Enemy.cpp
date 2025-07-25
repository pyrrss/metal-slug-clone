#include <iostream>

#include "Enemy.hpp"

Enemy::Enemy(Vector2 position, Vector2 velocity, int health, int damage) : Entity(position, velocity)
{
    // se llama inmediatamente al constructor de Entity y se le pasan sus parámetros (posición, tamaño, velocidad)
    
    this->m_health = health;
    this->m_damage = damage;
    
    this->m_object_type = GameObjectType::ENEMY;

}
