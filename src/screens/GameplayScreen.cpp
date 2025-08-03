#include <iostream>
#include <memory>
#include <algorithm>

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


    // NOTE: ya no es necesario delete, ya que se está usando unique_ptr y se gestiona automáticamente
    // for (Entity* entity : m_entities)
    // {
    //     delete entity;
    // }
    //
    // for (Platform* platform : m_platforms)
    // {
    //     delete platform;
    // }

}

void GameplayScreen::init()
{
    m_floor = { 0, (float) GetScreenHeight() - 50, (float) GetScreenWidth(), 50 };

    // NOTE: TODO ESTO ES PARA TESTEAR COSAS Y FUNCIONALIDADES 

    Vector2 player_pos = { (float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    Vector2 player_velocity = { 0.0f, 0.0f };
    float player_scale = 4.0f;   

    std::unique_ptr<Player> player = std::make_unique<Player> (player_pos, player_velocity, player_scale);
    player->equip_glock();
    m_entities.push_back(std::move(player));

    // -> se crean algunas plataformas de prueba
    // m_platforms.push_back(new Platform({ 500, 500 }, 200, 20));
    // m_platforms.push_back(new Platform({ 800, 400 }, 200, 20));
    // m_platforms.push_back(new Platform({ 200, 300 }, 200, 20));
}

game_screen GameplayScreen::update()
{
    // --- Manejo de Input ---
    Player* player = nullptr;
    for (const std::unique_ptr<Entity>& entity : m_entities)
    {
        // -> se intenta castear a Player
        player = dynamic_cast<Player*>(entity.get());
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

        if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            player->dash();
        }
        
        // TODO: ver si hay un mejor boton para disparar
        if (IsKeyPressed(KEY_E))
        {
            std::unique_ptr<Bullet> bullet = player->get_current_weapon()->shoot();
            
            if (bullet != nullptr)
            {
                m_bullets.push_back(std::move(bullet));
            }
        }


    }


    // --- ACTUALIZACION DE ENTIDADES ---
    
    // -> se actualizan todas las entidades 
    for (const std::unique_ptr<Entity>& entity : m_entities)
    {
        entity->update();
    }
    
    for (const std::unique_ptr<Bullet>& bullet : m_bullets)
    {
        bullet->update();
    }

    // -> limpieza de bullets inactivas
    m_bullets.erase( // NOTE: no entiendo esta sintaxis rara 
            std::remove_if(m_bullets.begin(), m_bullets.end(), [](const std::unique_ptr<Bullet>& bullet) {
                return !bullet->is_active();
            }),
            m_bullets.end()
    );

    // -> colisiones entidad-suelo
    for (const std::unique_ptr<Entity>& entity : m_entities)
    {
        if (CheckCollisionRecs(entity->get_bounding_box(), m_floor))
        {
            entity->on_collision_with_floor(m_floor);
        }
    }

    // -> colisiones entidad-plataforma
    for (std::unique_ptr<Entity>& entity : m_entities)
    {
        for (std::unique_ptr<Platform>& platform : m_platforms)
        {
            if (CheckCollisionRecs(entity->get_bounding_box(), platform->get_bounding_box()))
            {
                entity->on_collision_with_platform(dynamic_cast<Platform*>(platform.get()));
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
    for (std::unique_ptr<Entity>& entity : m_entities)
    {
        entity->render();
    }

    for (std::unique_ptr<Bullet>& bullet : m_bullets)
    {
        bullet->render();
    }


    DrawRectangleRec(m_floor, DARKGRAY);


}
