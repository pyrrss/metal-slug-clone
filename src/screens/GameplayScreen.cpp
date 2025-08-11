#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "GameplayScreen.hpp"
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/EnemyFactory.hpp"
#include "../entities/Platform.hpp"
#include "../managers/TextureManager.hpp"

#include "../core/ParallaxLayer.hpp"

GameplayScreen::GameplayScreen()
{


}

GameplayScreen::~GameplayScreen()
{
    std::cout << "LOG: GameplayScreen destruido" << std::endl;
}

void GameplayScreen::init()
{
 
    // --- WORLD SETUP ---

    m_floor = { -2000, 700.0f, 10000, 10000 };

    // --- PLAYER ---
    // -> se posiciona al jugador en relación al suelo
    Vector2 player_pos = { (float) 0.0f, 650.0f };
    Vector2 player_velocity = { 0.0f, 0.0f };
    float player_scale = 4.0f;   

    m_player = std::make_unique<Player> (player_pos, player_velocity, player_scale);
    m_player->equip_glock();

    // --- CAMERA ---
    m_camera.target = m_player->get_position();
    m_camera.offset = { (float) GetScreenWidth() / 2.0f - 100.0f, (float) GetScreenHeight() / 2.0f + 100.0f }; // -> jugador aparece en el centro 50 pixeles izq. y 100 pixeles más abajo
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;


    // --- ENEMIES ---
    EnemyStats skeleton_stats = EnemyFactory::create_skeleton_stats();

    // -> se posiciona al enemigo en relación al suelo
    Vector2 start_enemy_pos = { 400.0f, 650.0f };
    
    for (int i = 0; i < 5; i++)
    {
        Vector2 current_enemy_pos = { (float) start_enemy_pos.x + i * 300, start_enemy_pos.y };
        Vector2 enemy_velocity = { 0.0f, 0.0f };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy> (current_enemy_pos, enemy_velocity, skeleton_stats);
        m_enemies.push_back(std::move(enemy));
    }

    // -> se crean algunas plataformas de prueba
    // m_platforms.push_back(new Platform({ 500, 500 }, 200, 20));
    // m_platforms.push_back(new Platform({ 800, 400 }, 200, 20));
    // m_platforms.push_back(new Platform({ 200, 300 }, 200, 20));


    // --- PARALLAX LAYERS BG ---
    // NOTE: se ordenan de capa más lejana a más cercana := z-ordering
    
    ParallaxLayer layer6_bg = { TextureManager::get_texture("layer6_bg"), { 0, 0 }, 0.1f };
    ParallaxLayer layer5_bg = { TextureManager::get_texture("layer5_bg"), { 0, 0 }, 0.25f };
    ParallaxLayer layer4_bg = { TextureManager::get_texture("layer4_bg"), { 0, 0 }, 0.4f };
    ParallaxLayer layer3_bg = { TextureManager::get_texture("layer3_bg"), { 0, 0 }, 0.5f };
    ParallaxLayer layer2_bg = { TextureManager::get_texture("layer2_bg"), { 0, 0 }, 0.75f };
    ParallaxLayer layer1_bg = { TextureManager::get_texture("layer1_bg"), { 0, 0 }, 0.9f };

    m_parallax_layers.push_back(layer6_bg);
    m_parallax_layers.push_back(layer5_bg);
    m_parallax_layers.push_back(layer4_bg);
    m_parallax_layers.push_back(layer3_bg);
    m_parallax_layers.push_back(layer2_bg);
    m_parallax_layers.push_back(layer1_bg);

}

game_screen GameplayScreen::update()
{
    // --- Manejo de Input del Jugador ---
    if (m_player)
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
            m_player->move(move_dir);
        }
        else
        {
            m_player->stop_move();
        }

        if (IsKeyPressed(KEY_W))
        {
            m_player->jump();
        }

        if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            m_player->dash();
        }
 
        if (IsKeyPressed(KEY_F))
        {
            m_player->attack();
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            std::unique_ptr<Bullet> bullet = m_player->get_current_weapon()->shoot();
            
            if (bullet != nullptr)
            {
                m_bullets.push_back(std::move(bullet));
            }
        }
    }

    // --- input de Debug para Enemigos ---
    if (IsKeyPressed(KEY_ONE))
    {
        for (auto& enemy : m_enemies)
        {
            enemy->attack();
        }
    }

    if (IsKeyPressed(KEY_TWO))
    {
        for (auto& enemy : m_enemies)
        {
            enemy->die();
        }
    }

    // -> input para ajustar cámara
    if (IsKeyDown(KEY_COMMA))
    {
        m_camera.zoom += 0.01f;
        
        if (m_camera.zoom > 3.0f)
        {
            m_camera.zoom = 3.0f;
        }
    }

    if (IsKeyDown(KEY_PERIOD))
    {
        m_camera.zoom -= 0.01f;
        
        if (m_camera.zoom < 0.1f)
        {
            m_camera.zoom = 0.1f;
        }
    }



    // --- ACTUALIZACION DE ENTIDADES ---
    
    // -> Actualizar jugador y cámara 
    if (m_player)
    {
        m_player->update();
        m_camera.target = m_player->get_position();
    }

    // -> actualizar enemigos y su IA
    for (auto& enemy : m_enemies)
    {
        enemy->update();
        if (m_player)
        {
            enemy->update_ai(*m_player);
        }
    }
    
    // -> actualizar balas
    for (auto& bullet : m_bullets)
    {
        bullet->update();
    }

    // -> limpieza de balas inactivas
    // NOTE: no entiendo esta sintaxis rara pero funciona
    m_bullets.erase(
            std::remove_if(m_bullets.begin(), m_bullets.end(), [](const std::unique_ptr<Bullet>& bullet) {
                return !bullet->is_active();
            }),
            m_bullets.end()
    );

    // --- COLISIONES ---

    // -> colisión del jugador con el suelo
    if (m_player && CheckCollisionRecs(m_player->get_bounding_box(), m_floor))
    {
        m_player->on_collision_with_floor(m_floor);
    }

    // -> colisión de enemigos con el suelo
    for (auto& enemy : m_enemies)
    {
        if (CheckCollisionRecs(enemy->get_bounding_box(), m_floor))
        {
            enemy->on_collision_with_floor(m_floor);
        }
    }
    
    // -> colisiones con plataformas (si las hubiera)
    // ...

    // -> colisiones entre entidades (Jugador con Enemigo)
    if (m_player)
    {
        for (auto& enemy : m_enemies)
        {
            if (CheckCollisionRecs(m_player->get_bounding_box(), enemy->get_bounding_box()))
            {
                m_player->on_collision_with_entity(enemy.get());
                enemy->on_collision_with_entity(m_player.get());
            }
        }
    }

    return game_screen::NONE;
}

void GameplayScreen::render()
{
    ClearBackground(RAYWHITE);
 
    // -> baackground parallax
    for (auto& layer : m_parallax_layers)
    {
        float scale = (float) GetScreenHeight() / layer.texture.height;
        float scaled_width = layer.texture.width * scale;

        float offset_x = fmodf(m_camera.target.x * layer.scroll_speed, scaled_width);
    
        float start_x = -offset_x; // -> posición inicial para empezar a renderizar
        if (start_x > 0)
        {
            start_x -= scaled_width;
        }

        for (float x = start_x; x < GetScreenWidth(); x += scaled_width)
        {
            DrawTextureEx(layer.texture, { x, 0 }, 0.0f, scale, WHITE);
        }
    }

    // -> se inicia modo de renderizado 2d con la cámara
    // NOTE: todo lo que se dibuje dentro de bloque BeginMode2D se renderiza desde la perspectiva de la 
    // cámara
    BeginMode2D(m_camera);

    // -> se dibuja el suelo
    DrawRectangleRec(m_floor, DARKGRAY);

    // -> renderizar jugador
    if (m_player)
    {
        m_player->render();
    }

    // -> renderizar enemigos
    for (auto& enemy : m_enemies)
    {
        enemy->render();
    }

    // -> renderizar balas
    for (auto& bullet : m_bullets)
    {
        bullet->render();
    }


    EndMode2D();

    
    // -> a partir de acá se dibujan elementos estáticos de la ui que van fijos en pantalla
    int font_width = MeasureText("Pantalla de juego", 40);
    DrawText("Pantalla de juego", GetScreenWidth() / 2 - font_width / 2, 50, 40, BLACK);

}
