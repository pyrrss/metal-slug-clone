#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

#include "Platform.hpp"
#include "GameObject.hpp"

class Entity : public GameObject
{
    protected:

        Vector2 m_velocity;
        float m_gravity_scale; // -> porcentaje de gravedad que recibe cada entidad

        

    public:
        Entity(Vector2 position, Vector2 velocity);
        virtual ~Entity() = default;

        virtual void update() = 0;
        virtual void render() = 0;

        virtual void on_collision_with_floor(Rectangle floor) = 0;
        virtual void on_collision_with_entity(Entity* entity) = 0;
        virtual void on_collision_with_platform(Platform* platform) = 0;

};











#endif
