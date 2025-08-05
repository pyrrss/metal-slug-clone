#include <iostream>
#include <memory>
#include <algorithm>

#include "raylib.h"
#include "raymath.h"

#include "GameplayScreen.hpp"
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/EnemyFactory.hpp"
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

    // --- ENEMIES ---
    EnemyStats skeleton_stats = EnemyFactory::create_skeleton_stats();

    Vector2 enemy_pos = { 700.0f, 500.0f };
    Vector2 enemy_velocity = { 0.0f, 0.0f };
    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy> (enemy_pos, enemy_velocity, skeleton_stats);
    m_entities.push_back(std::move(enemy));



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
    
        // TODO: quitar esto de aqui luego y manejarlo según comportamiento de enemigo
        if (entity->get_object_type() == GameObjectType::ENEMY)
        {
            entity->move(Vector2{ -1.0f, 0.0f });
        }
    }
    
    for (const std::unique_ptr<Bullet>& bullet : m_bullets)
    {
        bullet->update();
    }

    // -> limpieza de bullets inactivas
    m_bullets.erase( // NOTE: no entiendo esta sintaxis rara pero funciona
            std::remove_if(m_bullets.begin(), m_bullets.end(), [](const std::unique_ptr<Bullet>& bullet) {
                return !bullet->is_active();
            }),
            m_bullets.end()
    );

    // TODO: en un futuro manejar colisiones de mejor forma

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
    

    // -> colisiones entidad-entidad
    for (std::unique_ptr<Entity>& entity : m_entities)
    {
        for (std::unique_ptr<Entity>& other_entity : m_entities)
        {
            if (entity.get() != other_entity.get())
            {
                if (CheckCollisionRecs(entity->get_bounding_box(), other_entity->get_bounding_box()))
                {
                    entity->on_collision_with_entity(other_entity.get());
                    other_entity->on_collision_with_entity(entity.get());
                }
            }
        }
    }

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
