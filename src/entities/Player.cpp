#include <iostream>

#include "raylib.h"

#include "Player.hpp"
#include "../managers/TextureManager.hpp"


Player::Player(Vector2 position, Vector2 size, Vector2 velocity, float scale) : Entity(position, size, velocity)
{
    // se llama inmediatamente al constructor de Entity al instanciar jugador y se le pasan sus parámentros (posicion, tamaño, velocidad)
    this->m_scale = scale;

    // se llama inmediatamente al constructor de Entity al instanciar jugador y se le pasan sus parámentros (posicion, tamaño, velocidad)
    
    this->m_idle_texture = TextureManager::get_texture("player_idle");
    this->m_idle_frames_count = 10;
    
    // NOTE: los valores son extraídos directamente de cada spritesheet 
    // formato: { x, y, ancho, alto }
    this->m_idle_frames[0] = { 36, 47, 20, 34 };
    this->m_idle_frames[1] = { 132, 48, 21, 33 }; 
    this->m_idle_frames[2] = { 228, 49, 21, 32 }; 
    this->m_idle_frames[3] = { 324, 50, 21, 31 };
    this->m_idle_frames[4] = { 419, 49, 21, 32 }; 
    this->m_idle_frames[5] = { 514, 49, 22, 32 }; 
    this->m_idle_frames[6] = { 610, 49, 22, 32 }; 
    this->m_idle_frames[7] = { 706, 49, 22, 32 }; 
    this->m_idle_frames[8] = { 802, 49, 22, 32 }; 
    this->m_idle_frames[9] = { 899, 47, 21, 34 }; 

    // -> inicializar el estado de la animación
    this->m_current_frame = 0;
    this->m_frames_counter = 0;
    this->m_frames_speed = 8; // -> velocidad de animación (8 frames por segundo)
}

Player::~Player() {}

void Player::update()
{
    m_frames_counter++;

    if (m_frames_counter >= (GetFPS() / m_frames_speed))
    {
        m_frames_counter = 0;
        m_current_frame++;

        if (m_current_frame >= m_idle_frames_count)
        {
            m_current_frame = 0; // -> reiniciar animación
        }
    }

    // TODO: actualizar otras cosas específicas del jugador (movimiento, input, ...)
    // -------------------------------------------------------------------------------
    float speed = 200.0f; // -> velocidad de movimiento en píxeles por segundo
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, speed * GetFrameTime()));
    // ------------------------------------------------------------------------------
}

void Player::render()
{
    // -> se toma el rectangulo del frame actual
    Rectangle source_rec = m_idle_frames[m_current_frame];
    
    // -> rectangulo de destino a partir de source_rec y escalado
    Rectangle dest_rec = {
        m_position.x,
        m_position.y,
        source_rec.width * m_scale,
        source_rec.height * m_scale
    };

    // -> se dibuja la textura con el escalado aplicado
    DrawTexturePro(m_idle_texture, source_rec, dest_rec, {0, 0}, 0.0f, WHITE);
}

// --- Implementación de Acciones ---

void Player::move(Vector2 direction)
{
    m_velocity = Vector2Normalize(direction);
}

void Player::stop_move()
{
    m_velocity = { 0, 0 };
}

void Player::jump()
{
    std::cout << "jugador salta, aun no hace nada" << std::endl;
}



