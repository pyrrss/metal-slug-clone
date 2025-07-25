#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "GameplayScreen.hpp"
#include "../entities/Player.hpp"
#include "../entities/Platform.hpp"

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

    for (Platform* platform : m_platforms)
    {
        delete platform;
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

    // -> se crean algunas plataformas de prueba
    // m_platforms.push_back(new Platform({ 500, 500 }, 200, 20));
    // m_platforms.push_back(new Platform({ 800, 400 }, 200, 20));
    // m_platforms.push_back(new Platform({ 200, 300 }, 200, 20));
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

        if (IsKeyPressed(KEY_E))
        {
            player->dash();
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

    // -> colisiones entidad-plataforma
    for (Entity* entity : m_entities)
    {
        for (Platform* platform : m_platforms)
        {
            if (CheckCollisionRecs(entity->get_bounding_box(), platform->get_bounding_box()))
            {
                entity->on_collision_with_platform(platform);
            }
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

    for (Platform* platform : m_platforms)
    {
        platform->render();
    }

    DrawRectangleRec(m_floor, DARKGRAY);


}
