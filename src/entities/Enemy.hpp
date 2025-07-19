#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "raymath.h"

#include "Entity.hpp"



class Enemy : public Entity
{
    protected:
        int m_health;
        int m_damage;

    public:
        Enemy(Vector2 position, Vector2 size, Vector2 velocity, int health, int damage);
        ~Enemy() = default;
        

        // NOTE: cada tipo de enemigo particular (ej: soldier, alien, ...) es el que implementa update() y render()
};













#endif
