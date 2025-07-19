#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raymath.h"

#include "Entity.hpp"


class Player : public Entity
{
    public:
        Player(Vector2 position, Vector2 size, Vector2 velocity);
        ~Player();
        void update() override;
        void render() override;


};










#endif
