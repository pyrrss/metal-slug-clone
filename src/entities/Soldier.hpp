#ifndef SOLDIER_HPP
#define SOLDIER_HPP


#include "Enemy.hpp"

class Soldier : public Enemy
{
    public:
        Soldier(Vector2 position, Vector2 velocity, int health, int damage);
        ~Soldier();

        void update() override;
        void render() override;
    
        void on_collision_with_floor(Rectangle floor) override;
        void on_collision_with_entity(Entity* entity) override;
        void on_collision_with_platform(Platform* platform) override;
};

















#endif
