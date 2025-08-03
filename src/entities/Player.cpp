#include <cmath>
#include <iostream>

#include "Entity.hpp"
#include "GameObject.hpp"
#include "raylib.h"
#include "raymath.h"

#include "Player.hpp"
#include "../managers/TextureManager.hpp"
#include "../entities/WeaponFactory.hpp"


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
    m_dash_speed = 1000.0f;
    m_dash_cooldown = 1.5f;
    m_dash_cooldown_timer = 0.0f;
    m_dash_duration = 0.3f;
    m_dash_duration_timer = 0.0f;
    m_can_dash = true;
    
    m_current_weapon = nullptr;

    setup_animations();
    setup_weapon_anchor_points();
}

Player::~Player() 
{
    std::cout << "LOG: Player destruido" << std::endl;
    
    if (m_current_weapon != nullptr)
    {
        delete m_current_weapon;
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
                m_current_animation_frame = current_animation.frame_count - 1; // -> se queda en último frame
            }

        }
    }
    
    // ------- DASH ------
    
    // -> duracion de dash
    if (m_player_state == PlayerState::DASHING && m_dash_duration_timer > 0.0f)
    {
        m_dash_duration_timer -= GetFrameTime();
    }
    else if (m_player_state == PlayerState::DASHING)
    {
        stop_dash();
    }


    // -> cooldown de dash
    if (m_dash_cooldown_timer > 0.0f)
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


    // --- WEAPON ---
    if (m_current_weapon != nullptr)
    {
        auto it = m_weapon_anchor_points.find(m_player_state); // -> se busca el par segun el estado actual del jugador
        if (it != m_weapon_anchor_points.end())
        {
            const std::vector<Vector2>& anchor_points = it->second; // -> se extrae vector de puntos de anclaje
            
            // -> se comprueba que el frame actual de la animacion tenga un punto de anclaje definido
            if (m_current_animation_frame < (int) anchor_points.size())
            {
                Rectangle current_frame_rect = current_animation.frames[m_current_animation_frame];
                Vector2 anchor_point = anchor_points[m_current_animation_frame];
                
                // -> se calcula offset del punto de anclaje relativo al frame actual.
                Vector2 relative_offset = Vector2Subtract(anchor_point, {current_frame_rect.x, current_frame_rect.y});
                Vector2 scaled_offset = Vector2Scale(relative_offset, m_scale);

                float scaled_sprite_height = fabsf(current_frame_rect.height) * m_scale;
                float y_offset = m_bounding_box.height - scaled_sprite_height;


                // -> se calcula la posicion final del arma
                Vector2 weapon_position;
                if (m_facing_direction == 1) // -> mirando a la derecha
                {
                    weapon_position = {
                        m_position.x + scaled_offset.x,
                        m_position.y + y_offset + scaled_offset.y
                    };
                }
                else if (m_facing_direction == -1)// -> mirando a la izquierda
                {
                    float scaled_sprite_width = fabsf(current_frame_rect.width) * m_scale;
                    weapon_position = {
                        m_position.x + scaled_sprite_width - scaled_offset.x,
                        m_position.y + y_offset + scaled_offset.y
                    };
                }

                m_current_weapon->update_transform(weapon_position, m_facing_direction);
            }
        }

        m_current_weapon->update();
    }

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

    // --- WEAPON ---
    if (m_current_weapon != nullptr)
    {
        m_current_weapon->render();
    }

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
    // Rectangle platform_box = platform->get_bounding_box();
    // Rectangle player_box = get_bounding_box();
    
    // TODO: hacer manejo de colisiones con plataformas, de forma vertical y por los lados
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

void Player::jump()
{
    if (m_player_state == PlayerState::DASHING || m_player_state == PlayerState::JUMPING) 
    {
        return;
    }

    
    m_player_state = PlayerState::JUMPING;
    m_current_animation_frame = 0;

    m_velocity.y = -450.0f;


}

void Player::dash()
{
    if (!m_can_dash || m_player_state == PlayerState::DASHING)
    {
        return;
    }

    m_player_state = PlayerState::DASHING;
    m_current_animation_frame = 0;

    m_can_dash = false;
    m_dash_cooldown_timer = m_dash_cooldown;

    m_gravity_scale = 0.0f; // -> ignora gravedad durante dash
    m_velocity.y = 0; // -> dash solo horizontal
    m_velocity.x = m_dash_speed * m_facing_direction;

    m_dash_duration_timer = m_dash_duration;


}

void Player::stop_dash()
{
    m_player_state = PlayerState::IDLE;
    m_current_animation_frame = 0;
    m_velocity = { 0, 0 }; // -> restaurar velocidad
    m_gravity_scale = 1.0f; // -> restaurar gravedad
    m_dash_duration_timer = 0.0f;
}

Weapon* Player::get_current_weapon() const
{
    return m_current_weapon;
}

void Player::equip_glock()
{
    if (m_current_weapon != nullptr)
    {
        delete m_current_weapon;
    }

    WeaponStats glock_stats = WeaponFactory::create_glock_stats();
    m_current_weapon = new Weapon(m_position, glock_stats);
}

void Player::equip_ak47()
{
    if (m_current_weapon != nullptr)
    {
        delete m_current_weapon;
    }

    WeaponStats ak47_stats = WeaponFactory::create_ak47_stats();
    m_current_weapon = new Weapon(m_position, ak47_stats);
}





void Player::setup_animations()
{
    
    // ------------- SPRITESHEETS DE WARRIOR --------------
    
    // ------------- ANIMACION IDLE -------------
    Animation idle_animation;
    idle_animation.texture = TextureManager::get_texture("player_idle");
    idle_animation.frame_count = 6;
    idle_animation.frame_speed = 10; // -> frames por segundo
    idle_animation.loops = true;
    idle_animation.frames = 
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
    running_animation.frames =
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
    jumping_animation.frames =
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
    dashing_animation.frame_speed = 25; // -> frames por segundo
    dashing_animation.loops = false;
    dashing_animation.frames =
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

    // -> inicializar timer de frames para mantener velocidad de animación
    this->m_frames_timer = 0.0f;
}

void Player::setup_weapon_anchor_points()
{
    // TODO: rellenar map de estados a vec de puntos de anclaje   
    
    m_weapon_anchor_points[PlayerState::IDLE] = 
    {
        { 35, 28 },
        { 98, 28 },
        { 164, 27 },
        { 228, 29 },
        { 35, 74 },
        { 99, 72 },
    };


    m_weapon_anchor_points[PlayerState::RUNNING] = 
    {
        { 35, 24 },
        { 99, 21 },
        { 164, 24 },
        { 227, 27 },
        { 40, 71 },
        { 104, 68 },
        { 167, 70 },
        { 225, 72 }
    };

    m_weapon_anchor_points[PlayerState::JUMPING] = 
    {
        { 38, 25 },
        { 102, 24 },
        { 166, 25 },
    };
    
    m_weapon_anchor_points[PlayerState::DASHING] =
    {
        { 40, 27 },
        { 110, 27 },
        { 179, 27 },
        { 248, 27 },
        { 35, 70 },
        { 104, 69 },
        { 173, 71 }
    };



}
