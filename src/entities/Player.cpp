#include <cmath>
#include <iostream>

#include "Entity.hpp"
#include "GameObject.hpp"
#include "raylib.h"
#include "raymath.h"

#include "Player.hpp"
#include "../managers/TextureManager.hpp"




Player::Player(Vector2 position, Vector2 velocity, float scale) : Entity(position, velocity)
{
    // se llama inmediatamente al constructor de Entity al instanciar jugador y se le pasan sus parámentros (posicion, tamaño, velocidad)
    this->m_movement_direction = {0, 0};
    this->m_player_state = PlayerState::IDLE; // -> por defecto está quieto
    this->m_facing_direction = 1; // -> por defecto mira a la derecha
    this->m_velocity = velocity;
    this->m_scale = scale;
    this->m_gravity_scale = 1.0f;

    this->m_object_type = GameObjectType::PLAYER;

    // --- Inicialización de Dash ---
    this->m_can_dash = true;
    this->m_dash_duration = 0.01f; 
    this->m_dash_timer = 0.0f;
    this->m_dash_speed = 800.0f; 
    this->m_dash_cooldown = 1.0f; // 1 segundo de cooldown
    this->m_dash_cooldown_timer = 0.0f;


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
    // m_player_state = PlayerState::IDLE;


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
                if (m_player_state == PlayerState::DASHING)
                {
                    stop_dash();
                }
                else
                {
                    m_current_animation_frame = current_animation.frame_count - 1;
                }
            }

        }
    }
    
    // --- CD DASH ---
    if (m_dash_cooldown_timer > 0)
    {
        m_dash_cooldown_timer -= GetFrameTime();
    }
    else
    {
        m_can_dash = true;
    }


    // --- Lógica de movimiento y gravedad ---
    if (m_player_state != PlayerState::DASHING)
    {
        // -> se aplica velocidad de movimiento según dirección y velocidad del jugador
        float speed = 400.0f; // -> velocidad de movimiento en píxeles por segundo
        m_velocity.x = m_movement_direction.x * speed;

        // -> se aplica gravedad
        const float GRAVITY = 980.0f; // Aceleración gravitacional en píxeles/segundo^2
        m_velocity.y += m_gravity_scale * GRAVITY * GetFrameTime();
    }


    // -> se actualiza la posición según velocidad y dirección
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, GetFrameTime()));

    // -> se actualiza rectangulo del jugador
    m_bounding_box.x = m_position.x;
    m_bounding_box.y = m_position.y;
    
    // -> se actualiza el rectangulo del jugador según el frame actual y escala
    Rectangle current_frame_rect = current_animation.frames[m_current_animation_frame];
    m_bounding_box.width = current_frame_rect.width * m_scale;
    m_bounding_box.height = 33 * m_scale; // -> se fija la altura para evitar problemas de colisión


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

    // -> se calcula la altura del sprite actual escalado
    float scaled_sprite_height = fabsf(source_rec.height) * m_scale;

    // -> se calcula el offset 'y' para alinear el sprite con la parte inferior de bounding_box
    float y_offset = m_bounding_box.height - scaled_sprite_height;


    // -> rectangulo de destino a partir de source_rec y escalado
    Rectangle dest_rec = {
        m_position.x,
        m_position.y + y_offset, // se suma offset para alinear visualmente el sprite
        fabsf(source_rec.width) * m_scale,
        scaled_sprite_height 
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

    if (m_player_state == PlayerState::JUMPING || m_player_state == PlayerState::DASHING)
    {
        m_player_state = PlayerState::IDLE;
        m_current_animation_frame = 0;
    }
}

void Player::on_collision_with_platform(Platform* platform)
{
    Rectangle platform_box = platform->get_bounding_box();
    Rectangle player_box = get_bounding_box();

    // The player's position in the previous frame
    Vector2 previous_position = Vector2Subtract(m_position, Vector2Scale(m_velocity, GetFrameTime()));
    float previous_player_bottom = previous_position.y + player_box.height;

    // 1. Check for landing on the platform (top collision)
    if (m_velocity.y > 0 &&                                     // Is moving down
        previous_player_bottom <= platform_box.y &&             // Was above the platform
        player_box.y + player_box.height >= platform_box.y)     // Is now intersecting the platform top
    {
        // Make sure it's not a side graze while falling
        if ((player_box.x + player_box.width > platform_box.x) && (player_box.x < platform_box.x + platform_box.width))
        {
            m_velocity.y = 0;
            m_position.y = platform_box.y - player_box.height;

            if (m_player_state == PlayerState::JUMPING || m_player_state == PlayerState::DASHING)
            {
                m_player_state = PlayerState::IDLE;
                m_current_animation_frame = 0;
            }
            return; // Collision handled, no need to check for sides
        }
    }

    if ((player_box.y + player_box.height > platform_box.y) && (player_box.y < platform_box.y + platform_box.height))
    {
        if (m_velocity.x < 0 &&                                     
            player_box.x <= platform_box.x + platform_box.width &&  
            previous_position.x >= platform_box.x + platform_box.width)
        {
            m_position.x = platform_box.x + platform_box.width;
            m_velocity.x = 0;
        }
        else if (m_velocity.x > 0 &&                                
                 player_box.x + player_box.width >= platform_box.x && 
                 previous_position.x + player_box.width <= platform_box.x)
        {
            m_position.x = platform_box.x - player_box.width;
            m_velocity.x = 0;
        }
    }
}

void Player::on_collision_with_entity(Entity* entity)
{
    if (entity->get_object_type() == GameObjectType::ENEMY)
    {
        std::cout << "LOG: jugador colisiona con enemigo, no hace nada aún" << std::endl;
    }
}



// --- ACCIONES ---

void Player::move(Vector2 direction)
{
    if (m_player_state == PlayerState::DASHING) return;

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
    if (m_player_state == PlayerState::DASHING) return;

    if (m_player_state != PlayerState::IDLE && m_player_state != PlayerState::JUMPING)
    {
        m_player_state = PlayerState::IDLE;
        m_current_animation_frame = 0;
    }

    m_movement_direction = { 0, 0 };
}

// TODO: EL SALTO NO FUNCIONA CORRECTAMENTE; el problema es que la altura de los rectangulos varia segun la altura de los sprites, y hace que se buguee el salto
void Player::jump()
{
    if (m_player_state == PlayerState::DASHING) return;

    if (m_player_state != PlayerState::JUMPING)
    {
        m_player_state = PlayerState::JUMPING;
        m_current_animation_frame = 0;

        m_velocity.y = -450.0f;

    }

}

void Player::dash()
{
    if (!m_can_dash || m_player_state == PlayerState::DASHING) return;

    m_player_state = PlayerState::DASHING;
    m_current_animation_frame = 0;
    
    m_can_dash = false;
    m_dash_cooldown_timer = m_dash_cooldown;

    m_gravity_scale = 0.0f; // Ignorar gravedad durante el dash
    m_velocity.y = 0; // Dash puramente horizontal
    m_velocity.x = m_dash_speed * m_facing_direction;
}

void Player::stop_dash()
{
    m_player_state = PlayerState::IDLE;
    m_current_animation_frame = 0; 
    m_velocity = {0, 0};
    m_gravity_scale = 1.0f; // Restaurar gravedad
}

void Player::setup_animations()
{
    // ------------- SPRITESHEETS DE SAMURAI ------------

    // ------------- ANIMACION IDLE -------------
    // Animation idle_animation;
    // idle_animation.texture = TextureManager::get_texture("player_idle");
    // idle_animation.frame_count = 10;
    // idle_animation.frame_speed = 12; // -> frames por segundo
    // idle_animation.loops = true;
    // idle_animation.frames = new Rectangle[idle_animation.frame_count]
    // {
    //     { 36, 47, 20, 34 },
    //     { 132, 48, 21, 33 },
    //     { 228, 49, 21, 32 },
    //     { 324, 50, 21, 31 },
    //     { 419, 49, 21, 32 },
    //     { 514, 49, 22, 32 },
    //     { 610, 49, 22, 32 },
    //     { 706, 49, 22, 32 },
    //     { 802, 49, 22, 32 },
    //     { 899, 47, 21, 34 }
    // };
    //
    // m_animations[PlayerState::IDLE] = idle_animation; // -> mapea estado idle a su animación
    // -------------------------------------------

    // ------------- ANIMACION RUNNING -----------
    // Animation running_animation;
    // running_animation.texture = TextureManager::get_texture("player_running");
    // running_animation.frame_count = 16;
    // running_animation.frame_speed = 12; // -> frames por segundo
    // running_animation.loops = true;
    // running_animation.frames = new Rectangle[running_animation.frame_count]
    // {
    //     { 38, 52, 25, 32 },
    //     { 131, 52, 30, 32 },
    //     { 227, 51, 32, 32 },
    //     { 324, 50, 32, 32 },
    //     { 421, 50, 32, 32 },
    //     { 518, 52, 30, 32 },
    //     { 614, 53, 28, 32 },
    //     { 710, 54, 27, 32 },
    //     { 806, 54, 27, 32 },
    //     { 903, 53, 26, 32 },
    //     { 998, 51, 27, 32 },
    //     { 1093, 50, 31, 32 },
    //     { 1191, 51, 28, 32 },
    //     { 1288, 51, 25, 32 },
    //     { 1386, 52, 23, 32 },
    //     { 1482, 53, 23, 32 }
    // };
    // 
    // m_animations[PlayerState::RUNNING] = running_animation; // -> mapea estado corriendo a su animación

    // ------------ ANIMACION JUMPING ------------
    // Animation jumping_animation;
    // // TODO: aun no hay spritesheet de salto, por ahora se usa player_idle
    // jumping_animation.texture = TextureManager::get_texture("player_idle");
    // jumping_animation.frame_count = 1;
    // jumping_animation.frame_speed = 12;
    // jumping_animation.loops = false;
    // jumping_animation.frames = new Rectangle[jumping_animation.frame_count]
    // {
    //     { 36, 47, 20, 34}
    // };
    //
    // m_animations[PlayerState::JUMPING] = jumping_animation;
    
    // ------------- SPRITESHEETS DE WARRIOR --------------
    
    // ------------- ANIMACION IDLE -------------
    Animation idle_animation;
    idle_animation.texture = TextureManager::get_texture("player_idle");
    idle_animation.frame_count = 6;
    idle_animation.frame_speed = 10; // -> frames por segundo
    idle_animation.loops = true;
    idle_animation.frames = new Rectangle[idle_animation.frame_count]
    {
        { 18, 10, 18, 33 },
        { 82, 10, 18, 33 },
        { 145, 11, 20, 33 },
        { 209, 12, 20, 33 },
        { 18, 56, 18, 33 },
        { 82, 55, 18, 33 }
    };
    
    m_animations[PlayerState::IDLE] = idle_animation; // -> mapea estado idle a su animación

    // ------------- ANIMACION RUNNING -----------
    Animation running_animation;
    running_animation.texture = TextureManager::get_texture("player_running");
    running_animation.frame_count = 8;
    running_animation.frame_speed = 10; // -> frames por segundo
    running_animation.loops = true;
    running_animation.frames = new Rectangle[running_animation.frame_count]
    {
        { 12, 14, 25, 29 },
        { 77, 14, 24, 26 },
        { 140, 15, 29, 26 },
        { 203, 16, 26, 27 },
        { 12, 59, 29, 28 },
        { 77, 56, 28, 28 },
        { 139, 57, 29, 28 },
        { 207, 60, 22, 27 }
    };

    m_animations[PlayerState::RUNNING] = running_animation; // -> mapea estado corriendo a su animación
    
    // ------------- ANIMACION JUMPING ------------
    Animation jumping_animation;
    jumping_animation.texture = TextureManager::get_texture("player_jumping");
    jumping_animation.frame_count = 3;
    jumping_animation.frame_speed = 10; // -> frames por segundo
    jumping_animation.loops = true;
    jumping_animation.frames = new Rectangle[jumping_animation.frame_count]
    {
        { 19, 8, 20, 33 },
        { 83, 8, 20, 33 },
        { 147, 8, 20, 33 }
    };

    m_animations[PlayerState::JUMPING] = jumping_animation;

    // ------------- ANIMACION DASHING ------------
    Animation dashing_animation;
    dashing_animation.texture = TextureManager::get_texture("player_dashing");
    dashing_animation.frame_count = 7;
    dashing_animation.frame_speed = 10; // -> frames por segundo
    dashing_animation.loops = false;
    dashing_animation.frames = new Rectangle[dashing_animation.frame_count]
    {
        { 13, 15, 29, 28 },
        { 83, 15, 28, 28 },
        { 152, 15, 28, 28 },
        { 221, 15, 28, 28 },
        { 8, 59, 28, 28 },
        { 77, 59, 28, 28 },
        { 145, 56, 30, 31 },
    };
    
    m_animations[PlayerState::DASHING] = dashing_animation;

    // -> inicializar contador de frames para mantener velocidad de animación
    this->m_frames_timer = 0.0f;
}
