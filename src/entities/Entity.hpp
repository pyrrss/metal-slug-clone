#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

// NOTE: ir agregando los tipos de entidades acá
enum class EntityType
{
    PLAYER,
    ENEMY,
};


class Entity
{
    protected:

        Vector2 m_position;
        Vector2 m_velocity;
        float m_gravity_scale; // -> porcentaje de gravedad que recibe cada entidad

        Rectangle m_bounding_box;
        
        EntityType m_entity_type;

    public:
        Entity(Vector2 position, Vector2 velocity);
        virtual ~Entity() = default;

        virtual EntityType get_entity_type() const;
        virtual Rectangle get_bounding_box() const;

        virtual void update() = 0;
        virtual void render() = 0; 
        
        virtual void on_collision_with_floor(Rectangle floor) = 0;
        virtual void on_collision_with_entity(Entity* entity) = 0;

};











#endif
