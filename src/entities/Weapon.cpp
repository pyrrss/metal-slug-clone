#include <cmath>

#include "Weapon.hpp"
#include "../managers/TextureManager.hpp"

Weapon::Weapon(Vector2 position, const WeaponStats& stats) : GameObject(position), m_weapon_stats(stats)
{
    m_object_type = GameObjectType::WEAPON;
    
    m_weapon_state = WeaponState::IDLE;

    m_facing_direction = 1;

    m_current_animation_frame = 0;
    m_frames_timer = 0.0f;

}

void Weapon::update()
{
    const Animation& current_animation = m_weapon_stats.weapon_animations.at(m_weapon_state);
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
                if (m_weapon_state == WeaponState::SHOOTING || m_weapon_state == WeaponState::RELOADING)
                {
                    m_weapon_state = WeaponState::IDLE;
                    m_current_animation_frame = 0;
                } 
                else
                {
                    m_current_animation_frame = current_animation.frame_count - 1; // -> se queda en último frame
                }

            }

        }
    }

    // -> se actualiza rectangulo del jugador
    m_bounding_box.y = m_position.y;

    if (m_facing_direction == -1) // -> si jugador mira izquierda, se desplaza rectangulo hacia la izquierda
    {
        m_bounding_box.x = m_position.x - fabsf(current_animation.frames[m_current_animation_frame].width) * m_weapon_stats.weapon_scale;
    } else if (m_facing_direction == 1) // -> si jugador mira derecha, se ubica normal
    {
        m_bounding_box.x = m_position.x;
    }
    
    // -> se actualiza el rectangulo del jugador según el frame actual y escala
    Rectangle current_frame_rect = current_animation.frames[m_current_animation_frame];
    m_bounding_box.width = current_frame_rect.width * m_weapon_stats.weapon_scale;;
    m_bounding_box.height = 20 * m_weapon_stats.weapon_scale; // -> se fija la altura para evitar problemas de colisión

}

void Weapon::render()
{
     // -> se toma el rectangulo del frame actual
    const Animation& current_animation = m_weapon_stats.weapon_animations.at(m_weapon_state); // NOTE: se usa .at() ya que weapon_stats es const (y devuelve tambien const)
    Rectangle source_rec = current_animation.frames[m_current_animation_frame];

    // si direccion es -1, se invierte el ancho del rectangulo, esto en la práctica hace que al tomar el rectangulo
    // con ancho negativo sobre el spritesheet, este se rote a la izquierda.
    // fabsf es para asegurar positivo y no invertir un rectangulo que ya estaba invertido
    source_rec.width = fabsf(source_rec.width) * m_facing_direction;

    // -> rectangulo de destino a partir de source_rec y escalado
    Rectangle dest_rec = {
        m_position.x,
        m_position.y, // se suma offset para alinear visualmente el sprite
        fabsf(source_rec.width) * m_weapon_stats.weapon_scale,
        fabsf(source_rec.height) * m_weapon_stats.weapon_scale
    };
 
    // -> si jugador mira a la izquierda, se desplaza rectangulo hacia la izquierda
    if (m_facing_direction == -1)
    {

        dest_rec.x -= fabsf(source_rec.width) * m_weapon_stats.weapon_scale;
    }


    DrawTexturePro(current_animation.texture, source_rec, dest_rec, {0, 0}, 0.0f, WHITE);

    // ------------------ DEBUG -----------------
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, RED); // -> linea superior
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, RED); // -> linea derecha
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, RED); // -> linea inferior
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, RED); // -> linea izquierda
   
}

void Weapon::update_transform(Vector2 position, int facing_direction)
{
    m_position = position;
    m_facing_direction = facing_direction;
}

std::unique_ptr<Bullet> Weapon::shoot()
{
    if (m_weapon_state == WeaponState::SHOOTING || m_weapon_state == WeaponState::RELOADING)
    {
        return nullptr;
    }
    
    m_weapon_state = WeaponState::SHOOTING;
    m_current_animation_frame = 0;
    
    // Ahora pasamos la dirección del arma a la bala al crearla
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(m_position, m_facing_direction);
    return bullet;
}

Bullet::Bullet(Vector2 position, int facing_direction) : GameObject(position)
{
    m_object_type = GameObjectType::PROJECTILE;
    m_facing_direction = facing_direction; // -> Se guarda la dirección

    m_bullet_texture = TextureManager::get_texture("glock_bullet");

    m_bullet_speed = 800.0f;
    m_bullet_max_distance = 1000;
    m_bullet_current_distance = 0;
    
    m_is_active = true;

    m_bullet_scale = 5.0f;
    
    m_source_rec = {7, 7, 3, 2}; // -> lo defino aca ya que solo es una textura con un solo frame

    // NOTE: por ahora balas solo van horizontales, proximamente deberia permitir
    // en mas direcciones
    m_bounding_box.y = m_position.y;

    m_bounding_box.width = m_source_rec.width * m_bullet_scale;
    m_bounding_box.height = m_source_rec.height * m_bullet_scale;
}

void Bullet::update()
{
    m_bullet_current_distance += m_bullet_speed * GetFrameTime();

    if (m_bullet_current_distance >= m_bullet_max_distance)
    {
        m_is_active = false;
    }
    
    // La bala ahora usa su propia dirección para moverse
    m_position.x += m_bullet_speed * m_facing_direction * GetFrameTime();
    
    if (m_facing_direction == -1) // -> si va a izquierda, se desplaza recta hacia izquierda
    {
        m_bounding_box.x = m_position.x - fabsf(m_source_rec.width) * m_bullet_scale;
    } else if (m_facing_direction == 1)
    {
        m_bounding_box.x = m_position.x;
    }
  
}

void Bullet::render()
{
    
    // -> se invierte ancho si mira a la izquierda
    m_source_rec.width = fabsf(m_source_rec.width) * m_facing_direction;

    Rectangle dest_rec = {
        m_position.x,
        m_position.y,
        fabsf(m_source_rec.width) * m_bullet_scale,
        fabsf(m_source_rec.height) * m_bullet_scale
    };

    if (m_facing_direction == -1)
    {
        dest_rec.x -= fabsf(m_source_rec.width) * m_bullet_scale;
    }

    DrawTexturePro(m_bullet_texture, m_source_rec, dest_rec, {0, 0}, 0.0f, WHITE);

    // ------------------ DEBUG -----------------

    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, RED); // -> linea superior
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y, m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, RED); // -> linea derecha
    DrawLine(m_bounding_box.x + m_bounding_box.width, m_bounding_box.y + m_bounding_box.height, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, RED); // -> linea inferior
    DrawLine(m_bounding_box.x, m_bounding_box.y, m_bounding_box.x, m_bounding_box.y + m_bounding_box.height, RED); // -> linea izquierda

}

bool Bullet::is_active() const
{
    return m_is_active;
}



