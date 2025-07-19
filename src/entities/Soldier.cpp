#include <iostream>

#include "Soldier.hpp"

Soldier::Soldier(Vector2 position, Vector2 size, Vector2 velocity, int health, int damage) : Enemy(position, size, velocity, health, damage)
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
