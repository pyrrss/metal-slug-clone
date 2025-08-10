
#include "GameObject.hpp"

GameObject::GameObject(Vector2 position)
{
    this->m_position = position;
}

Vector2 GameObject::get_position() const
{
    return m_position;
}

GameObjectType GameObject::get_object_type() const
{
    return m_object_type;
}

Rectangle GameObject::get_bounding_box() const
{
    return m_bounding_box;
}
