#include <iostream>

#include "Entity.hpp"

Entity::Entity(Vector2 position, Vector2 velocity)
{
    this->m_position = position;
    this->m_velocity = velocity;
}

EntityType Entity::get_entity_type() const
{
    return m_entity_type;
}

Rectangle Entity::get_bounding_box() const
{
    return m_bounding_box;
}
