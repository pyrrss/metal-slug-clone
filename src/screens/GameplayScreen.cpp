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
    m_floor = { 0, (float) GetScreenHeight() - 50, (float) GetScreenWidth(), 50 };

    // NOTE: TODO ESTO ES PARA TESTEAR COSAS Y FUNCIONALIDADES 

    Vector2 player_pos = { (float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    Vector2 player_velocity = { 0.0f, 0.0f };
    float player_scale = 4.0f;   

    Player* player = new Player(player_pos, player_velocity, player_scale);
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


    // --- ACTUALIZACION DE ENTIDADES ---
    
    // -> se actualizan todas las entidades y se c
    for (Entity* entity : m_entities)
    {
        entity->update();
    }
 

    // -> colisiones entidad-suelo
    for (Entity* entity : m_entities)
    {
        if (CheckCollisionRecs(entity->get_bounding_box(), m_floor))
        {
            entity->on_collision_with_floor(m_floor);
        }
    }

    // TODO: hacer colisiones entidad-entidad

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

    DrawRectangleRec(m_floor, DARKGRAY);


}
