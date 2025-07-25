#include "Platform.hpp"
#include "raylib.h"

Platform::Platform(Vector2 position, float width, float height) : GameObject(position)
{
    this->m_object_type = GameObjectType::PLATFORM;
    this->m_bounding_box.x = position.x;
    this->m_bounding_box.y = position.y;
    this->m_bounding_box.width = width;
    this->m_bounding_box.height = height;
}

Platform::~Platform() {}

void Platform::render()
{
    DrawRectangleRec(m_bounding_box, BLUE);
}