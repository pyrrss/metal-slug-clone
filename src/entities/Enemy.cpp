#include <iostream>

#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "Enemy.hpp"
#include "Player.hpp"

#include "../core/PatrollingStrategy.hpp"
#include "../core/ChasingStrategy.hpp"
#include "../core/AttackingStrategy.hpp"

Enemy::Enemy(Vector2 position, Vector2 velocity, const EnemyStats& stats) : Entity(position, velocity), m_enemy_stats(stats)
{
    this->m_object_type = GameObjectType::ENEMY;
    
    this->m_enemy_state = EnemyState::IDLE;
    this->m_ai_state = AIState::PATROLLING;

    this->m_facing_direction = -1;

    this->m_current_animation_frame = 0;
    this->m_frames_timer = 0.0f;
    
    this->m_gravity_scale = 1.0f;

    this->m_movement_direction = { 0, 0 };

    set_ai_strategy(std::make_unique<PatrollingStrategy>());
}

void Enemy::update()
{
    const Animation& current_animation = m_enemy_stats.enemy_animations.at(m_enemy_state);
    
    m_frames_timer += GetFrameTime();

    if (m_frames_timer >= (1.0f / current_animation.frame_speed))
    {
        m_frames_timer = 0.0f;
        m_current_animation_frame++;

        if (m_current_animation_frame >= current_animation.frame_count)
        {
            if (current_animation.loops)
            {
                m_current_animation_frame = 0;
            }
            else
            {
                m_enemy_state = EnemyState::IDLE;
                m_current_animation_frame = 0;
            }



        }
    }

    // -> se aplica gravedad
    const float GRAVITY = 980.0f;    
    m_velocity.y += m_gravity_scale * GRAVITY * GetFrameTime();

    // -> se actualiza la posición según velocidad y dirección
    m_velocity.x = m_movement_direction.x * m_enemy_stats.enemy_speed;
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, GetFrameTime()));

        
    // -> se verifica que jugador no salga de la pantalla horizontalmente
    if (m_position.x < 0)
    {
        m_position.x = GetScreenWidth();
    } 
    else if (m_position.x > GetScreenWidth())
    {
        m_position.x = 0;
    }

    // -> se verifica que jugador no salga de la pantalla verticalmente
    if (m_position.y > GetScreenHeight())
    {
        m_position.y = 0;
    }
    else if (m_position.y < 0)
    {
        m_position.y = GetScreenHeight();
    }



    // -> se actualiza rectangulo de enemigo
    m_bounding_box.x = m_position.x;
    m_bounding_box.y = m_position.y;
    
    // -> se actualiza rect de enemigo según frame actual y escala
    Rectangle current_frame_rect = current_animation.frames[m_current_animation_frame];
    m_bounding_box.width = current_frame_rect.width * m_enemy_stats.enemy_scale;;
    m_bounding_box.height = 33 * m_enemy_stats.enemy_scale; // -> se fija la altura para evitar problemas de colisión


}

void Enemy::render()
{
         // -> se toma el rectangulo del frame actual
    const Animation& current_animation = m_enemy_stats.enemy_animations.at(m_enemy_state);
    Rectangle source_rec = current_animation.frames[m_current_animation_frame];

    // si direccion es -1, se invierte el ancho del rectangulo, esto en la práctica hace que al tomar el rectangulo
    // con ancho negativo sobre el spritesheet, este se rote a la izquierda.
    // fabsf es para asegurar positivo y no invertir un rectangulo que ya estaba invertido
    source_rec.width = fabsf(source_rec.width) * m_facing_direction;

    // -> rectangulo de destino a partir de source_rec y escalado
    Rectangle dest_rec = {
        m_position.x,
        m_position.y, // se suma offset para alinear visualmente el sprite
        fabsf(source_rec.width) * m_enemy_stats.enemy_scale,
        fabsf(source_rec.height) * m_enemy_stats.enemy_scale
    };
 


    DrawTexturePro(current_animation.texture, source_rec, dest_rec, {0, 0}, 0.0f, WHITE);

    // ------------------ DEBUG -----------------
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, BLUE); // -> linea superior
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, BLUE); // -> linea derecha
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, BLUE); // -> linea inferior
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, BLUE); // -> linea izquierda

}


// --- ACCIONES ---

void Enemy::move(Vector2 direction)
{
    if (m_enemy_state == EnemyState::DYING || m_enemy_state == EnemyState::ATTACKING)
    {
        return;
    }

    if (direction.x > 0)
    {
        m_facing_direction = 1; // -> está mirando a la derecha
    }
    else if (direction.x < 0)
    {
        m_facing_direction = -1; // -> está mirando a la izquierda
    }


    if (m_enemy_state != EnemyState::RUNNING)
    {
        m_enemy_state = EnemyState::RUNNING;
        m_current_animation_frame = 0;
    }

    m_movement_direction = Vector2Normalize(direction);

}

void Enemy::stop_move()
{
    if (m_enemy_state != EnemyState::IDLE)
    {
        m_enemy_state = EnemyState::IDLE;
        m_current_animation_frame = 0;
    }

    m_movement_direction = { 0, 0 };

}

void Enemy::attack()
{
    if (m_enemy_state == EnemyState::ATTACKING)
    {
        return;
    }

    m_enemy_state = EnemyState::ATTACKING;
    m_current_animation_frame = 0;
    m_movement_direction = { 0, 0 }; // -> se detiene para atacar

    // TODO: lo anterior es la parte de animacion, falta
    // manejar logica de ataque al jugador e inflingir daño


}

void Enemy::die()
{
    if (m_enemy_state == EnemyState::DYING)
    {
        return;
    }

    m_enemy_state = EnemyState::DYING;
    m_current_animation_frame = 0;
    m_movement_direction = { 0, 0 }; // -> se detiene para morir :v

    // TODO: lo anterior es la animacion, falta manejar logica
}



// --- COLISIONES ---

void Enemy::on_collision_with_floor(Rectangle floor)
{

    m_velocity.y = 0;
    m_position.y = floor.y - m_bounding_box.height;
}

void Enemy::on_collision_with_entity(Entity* entity)
{

    // NOTE: esto es de prueba, luego cambiar y recibir/inflingir daño
    
    // if (entity->get_object_type() == GameObjectType::PLAYER)
    // {
    //     stop_move();
    // }


}

void Enemy::on_collision_with_platform(Platform* platform)
{

}

// --- AI ---

bool Enemy::is_player_in_range(Player& player, float range)
{
    Vector2 enemy_center = 
    {
        m_bounding_box.x + m_bounding_box.width / 2,
        m_bounding_box.y + m_bounding_box.height / 2
    };
    
    Rectangle player_box = player.get_bounding_box();
    Vector2 player_center = 
    {
        player_box.x + player_box.width / 2,
        player_box.y + player_box.height / 2
    };
    
    // NOTE: se calcula la distancia al cuadrado para evitar calcular raiz cuadrada 
    float distance_sqr = Vector2DistanceSqr(enemy_center, player_center);

    return distance_sqr <= (range * range);
}

void Enemy::update_ai(Player& player)
{
    // el problema es la transicion de de Chase -> Patrol

    AIState previous_state = m_ai_state;

    switch (m_ai_state)
    {
        case AIState::PATROLLING:
        {
            if (is_player_in_range(player, m_enemy_stats.enemy_chase_range))
            {
                m_ai_state = AIState::CHASING;
            }

        } break;
        
        case AIState::CHASING:
        {
            if (is_player_in_range(player, m_enemy_stats.enemy_attack_range))
            {
                m_ai_state = AIState::ATTACKING;
            }

            if (!is_player_in_range(player, m_enemy_stats.enemy_chase_range))
            {
                m_ai_state = AIState::PATROLLING;
            }

        } break;
    
        case AIState::ATTACKING:
        {
            if (!is_player_in_range(player, m_enemy_stats.enemy_attack_range))
            {
                m_ai_state = AIState::CHASING;
            }

            // if (!is_player_in_range(player, m_enemy_stats.enemy_chase_range))
            // {
            //     m_ai_state = AIState::PATROLLING;
            // }

        } break;
    }
    
    if (previous_state != m_ai_state)
    {
        switch (m_ai_state)
        {
            case AIState::PATROLLING:
            {
                set_ai_strategy(std::make_unique<PatrollingStrategy>());
            } break;

            case AIState::CHASING:
            {
                set_ai_strategy(std::make_unique<ChasingStrategy>());
            } break;

            case AIState::ATTACKING:
            {
                set_ai_strategy(std::make_unique<AttackingStrategy>());
            } break;

        }

    }


    m_current_ai_strategy->update(*this, player);
}

void Enemy::set_ai_strategy(std::unique_ptr<AIStrategy> ai_strategy)
{
    m_current_ai_strategy = std::move(ai_strategy);
}
