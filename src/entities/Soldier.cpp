#include <iostream>

#include "Soldier.hpp"

Soldier::Soldier(Vector2 position, Vector2 velocity, int health, int damage) : Enemy(position, velocity, health, damage)
{
    // se llama inmediatamente al constructor de Enemy y se le pasan sus paŕametros (posición, tamño, velocidad, vida, daño)
    

}

Soldier::~Soldier() {}

void Soldier::update()
{

}

void Soldier::render()
{

}

void Soldier::on_collision_with_floor(Rectangle floor)
{

}

void Soldier::on_collision_with_entity(Entity* entity)
{

}
