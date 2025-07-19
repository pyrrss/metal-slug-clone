#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "raymath.h"

#include "Enemy.hpp"

class Soldier : public Enemy
{
    public:
        Soldier(Vector2 position, Vector2 size, Vector2 velocity, int health, int damage);
        ~Soldier();

        void update() override;
        void render() override;

};

















#endif
