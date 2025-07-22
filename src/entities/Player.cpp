#include <cmath>
#include <iostream>

#include "Entity.hpp"
#include "raylib.h"
#include "raymath.h"

#include "Player.hpp"
#include "../managers/TextureManager.hpp"


Player::Player(Vector2 position, Vector2 velocity, float scale) : Entity(position, velocity)
{
    // se llama inmediatamente al constructor de Entity al instanciar jugador y se le pasan sus parámentros (posicion, tamaño, velocidad)
    this->m_movement_direction = {0, 0};
    this->m_position = position;
    this->m_player_state = PlayerState::IDLE; // -> por defecto está quieto
    this->m_facing_direction = 1; // -> por defecto mira a la derecha
    this->m_velocity = velocity;
    this->m_scale = scale;
    this->m_gravity_scale = 1.0f;

    this->m_entity_type = EntityType::PLAYER;

    setup_animations();
}

Player::~Player() 
{
    std::cout << "LOG: Player destruido" << std::endl;

    for (auto& animation_pair : m_animations)
    {
        delete[] animation_pair.second.frames;
    }
}

void Player::update()
{
    Animation& current_animation = m_animations[m_player_state];
    m_frames_timer += GetFrameTime(); // -> se va sumando los delta times en cada frame

    if (m_frames_timer >= (1.0f / current_animation.frame_speed))
    {
        m_frames_timer = 0.0f; // -> reinicia contador de frames
        m_current_animation_frame++; // -> incrementa indice del frame actual en animación

        if (m_current_animation_frame >= current_animation.frame_count)
        {

            if (current_animation.loops)
            {
                m_current_animation_frame = 0; // -> reiniciar animación
            }
            else
            {
                m_current_animation_frame = current_animation.frame_count - 1; // -> se detiene la animación en el último frame por ahora
            }

        }
    }
    

    // TODO: actualizar otras cosas específicas del jugador (movimiento, input, ...)
    // -------------------------------------------------------------------------------
    
    // -> se actualiza el rectangulo del jugador según el frame actual y escala
    Rectangle current_frame_rect = current_animation.frames[m_current_animation_frame];
    m_bounding_box.width = current_frame_rect.width * m_scale;
    m_bounding_box.height = current_frame_rect.height * m_scale;

    // -> se aplica velocidad de movimiento según dirección y velocidad del jugador
    float speed = 400.0f; // -> velocidad de movimiento en píxeles por segundo
    m_velocity.x = m_movement_direction.x * speed;

    // -> se aplica gravedad
    const float GRAVITY = 980.0f; // Aceleración gravitacional en píxeles/segundo^2
    m_velocity.y += m_gravity_scale * GRAVITY * GetFrameTime();

    // -> se actualiza la posición según velocidad y dirección
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, GetFrameTime()));

    // -> se actualiza rectangulo del jugador
    m_bounding_box.x = m_position.x;
    m_bounding_box.y = m_position.y;


    // ------------------------------------------------------------------------------
}

void Player::render()
{
    // -> se toma el rectangulo del frame actual
    Animation& current_animation = m_animations[m_player_state];
    Rectangle source_rec = current_animation.frames[m_current_animation_frame];

    // TRUQUITO RAYLIB 
    // si direccion es -1, se invierte el ancho del rectangulo, esto en la práctica hace que al tomar el rectangulo
    // con ancho negativo sobre el spritesheet, este se rote a la izquierda.
    // fabsf es para asegurar positivo y no invertir un rectangulo que ya estaba invertido
    source_rec.width = fabsf(source_rec.width) * m_facing_direction;


    // -> rectangulo de destino a partir de source_rec y escalado
    Rectangle dest_rec = {
        m_position.x,
        m_position.y,
        fabsf(source_rec.width) * m_scale,
        source_rec.height * m_scale
    };
 

    DrawTexturePro(current_animation.texture, source_rec, dest_rec, {0, 0}, 0.0f, WHITE);

    // ------------------ DEBUG -----------------
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, GREEN); // -> linea superior
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, GREEN); // -> linea derecha
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, GREEN); // -> linea inferior
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, GREEN); // -> linea izquierda

}

// --- COLISIONES ---

void Player::on_collision_with_floor(Rectangle floor)
{
    m_velocity.y = 0;
    m_position.y = floor.y - m_bounding_box.height;
}

void Player::on_collision_with_entity(Entity* entity)
{
    if (entity->get_entity_type() == EntityType::ENEMY)
    {
        std::cout << "LOG: jugador colisiona con enemigo, no hace nada aún" << std::endl;
    }
}





// --- ACCIONES ---

void Player::move(Vector2 direction)
{
    if (direction.x > 0)
    {
        m_facing_direction = 1; // -> está mirando a la derecha
    }
    else if (direction.x < 0)
    {
        m_facing_direction = -1; // -> está mirando a la izquierda
    }


    if (m_player_state != PlayerState::RUNNING && m_player_state != PlayerState::JUMPING)
    {
        m_player_state = PlayerState::RUNNING;
        m_current_animation_frame = 0;
    }

    m_movement_direction = Vector2Normalize(direction);
}

void Player::stop_move()
{
    if (m_player_state != PlayerState::IDLE && m_player_state != PlayerState::JUMPING)
    {
        m_player_state = PlayerState::IDLE;
        m_current_animation_frame = 0;
    }

    m_movement_direction = { 0, 0 };
}

void Player::jump()
{
    // TODO: hacer lógica de salto y animación de salto
    // m_player_state = PlayerState::JUMPING;
    std::cout << "LOG: jugador salta, aun no hace nada" << std::endl;
}

void Player::setup_animations()
{
    // ------------- ANIMACION IDLE -------------
    Animation idle_animation;
    idle_animation.texture = TextureManager::get_texture("player_idle");
    idle_animation.frame_count = 10;
    idle_animation.frame_speed = 12; // -> frames por segundo
    idle_animation.loops = true;
    idle_animation.frames = new Rectangle[idle_animation.frame_count]
    {
        { 36, 47, 20, 34 },
        { 132, 48, 21, 33 },
        { 228, 49, 21, 32 },
        { 324, 50, 21, 31 },
        { 419, 49, 21, 32 },
        { 514, 49, 22, 32 },
        { 610, 49, 22, 32 },
        { 706, 49, 22, 32 },
        { 802, 49, 22, 32 },
        { 899, 47, 21, 34 }
    };

    m_animations[PlayerState::IDLE] = idle_animation; // -> mapea estado idle a su animación
    // -------------------------------------------

    // ------------- ANIMACION RUNNING -----------
    Animation running_animation;
    running_animation.texture = TextureManager::get_texture("player_running");
    running_animation.frame_count = 16;
    running_animation.frame_speed = 12; // -> frames por segundo
    running_animation.loops = true;
    running_animation.frames = new Rectangle[running_animation.frame_count]
    {
        { 38, 52, 25, 28 },
        { 131, 52, 30, 29 },
        { 227, 51, 32, 27 },
        { 324, 50, 32, 26 },
        { 421, 50, 32, 28 },
        { 518, 52, 30, 29 },
        { 614, 53, 28, 28 },
        { 710, 54, 27, 27 },
        { 806, 54, 27, 27 },
        { 903, 53, 26, 28 },
        { 998, 51, 27, 25 },
        { 1093, 50, 31, 24 },
        { 1191, 51, 28, 26 },
        { 1288, 51, 25, 30 },
        { 1386, 52, 23, 29 },
        { 1482, 53, 23, 28 }
    };
    
    m_animations[PlayerState::RUNNING] = running_animation; // -> mapea estado corriendo a su animación

    // -> inicializar contador de frames para mantener velocidad de animación
    this->m_frames_timer = 0.0f;
}
