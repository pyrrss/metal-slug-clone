#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "raylib.h"


enum class GameObjectType
{
    PLAYER,
    ENEMY,
    OBSTACLE,
    WEAPON,
    PLATFORM,
    ITEM,
    PROJECTILE,
};


class GameObject
{
    protected:

        Vector2 m_position;
        Rectangle m_bounding_box;
        GameObjectType m_object_type;

    public:
        GameObject(Vector2 position);
        virtual ~GameObject() = default;

        virtual void render() = 0;
        virtual void update() = 0;

        virtual Vector2 get_position() const;
        virtual GameObjectType get_object_type() const;
        virtual Rectangle get_bounding_box() const;




};






#endif
