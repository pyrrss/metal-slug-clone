#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "GameplayScreen.hpp"
#include "../entities/Player.hpp"

GameplayScreen::GameplayScreen()
{


}

GameplayScreen::~GameplayScreen()
{
    std::cout << "LOG: GameplayScreen destruido" << std::endl;

        

    for (Entity* entity : m_entities)
    {
        delete entity;
    }

}

void GameplayScreen::init()
{
    // NOTE: por ahora para probar añadiré entidades acá
    Vector2 player_pos = { (float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    Vector2 player_size = { 20, 34 };
    Vector2 player_velocity = { 0, 0 };
    
    Player* player = new Player(player_pos, player_size, player_velocity, 4);
    m_entities.push_back(player);
}

game_screen GameplayScreen::update()
{
    // --- Manejo de Input ---
    Player* player = nullptr;
    for (Entity* entity : m_entities)
    {
        // -> se intenta castear a Player
        player = dynamic_cast<Player*>(entity);
        if (player)
        {
            break; 
        }
    }

    if (player) // -> si se encuentra al jugador
    {
        Vector2 move_dir = { 0.0f, 0.0f };
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        {
            move_dir.x += 1.0f;
        }    
        
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        {
            move_dir.x -= 1.0f;
        }

        if (Vector2Length(move_dir) > 0.0f)
        {
            player->move(move_dir);
        }
        else
        {
            player->stop_move();
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            player->jump();
        }
    }


    // --- Actualización de Entidades ---
    for (Entity* entity : m_entities)
    {
        entity->update();
    }

    return game_screen::NONE;
}

void GameplayScreen::render()
{
    ClearBackground(RAYWHITE);
    
    int font_width = MeasureText("Pantalla de juego", 40);

    DrawText("Pantalla de juego", GetScreenWidth() / 2 - font_width / 2, 50, 40, BLACK);
    
    // -> renderizar entidades
    for (Entity* entity : m_entities)
    {
        entity->render();
    }


}
