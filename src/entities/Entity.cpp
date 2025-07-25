#include "Entity.hpp"

Entity::Entity(Vector2 position, Vector2 velocity) : GameObject(position)
{
    this->m_position = position;
    this->m_velocity = velocity;
}

void Entity::on_collision_with_platform(Platform* platform)
{
    // por defecto, las entidades no hacen nada al colisionar con plataformas
}