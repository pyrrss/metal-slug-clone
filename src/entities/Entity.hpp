#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "raymath.h"


class Entity
{
    protected:

        Vector2 m_position;
        Vector2 m_velocity;
        Vector2 m_size;
    
    public:
        Entity(Vector2 position, Vector2 size, Vector2 velocity);
        virtual ~Entity() = default;

        virtual void update() = 0;
        virtual void render() = 0; 


};











#endif
