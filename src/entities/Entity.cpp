#include <iostream>
#include <raymath.h>

#include "Entity.hpp"

Entity::Entity(Vector2 position, Vector2 size, Vector2 velocity)
{
    this->m_position = position;
    this->m_size = size;
    this->m_velocity = velocity;
}
