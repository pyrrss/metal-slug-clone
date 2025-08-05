#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>

#include "raylib.h"

#include "Entity.hpp"
#include "../core/Animation.hpp"
#include "Platform.hpp"
#include "Weapon.hpp"

// maquina estados del jugador
enum class PlayerState
{
    IDLE,
    RUNNING,
    JUMPING,
    DASHING,
    CROUCHING,
    HURT,
    DYING
};


class Player : public Entity
{
    private:

        // -> vars para controlar animaciones
        float m_frames_timer;
        int m_current_animation_frame;
        int m_facing_direction; // -> dirección donde se mira := 1 derecha, -1 izquierda, 0 vertical?
        
        PlayerState m_player_state;
        std::map<PlayerState, Animation> m_animations; // -> mapea estado de jugador a una animación
        
        float m_scale;

        Vector2 m_movement_direction;

        // --- DASH ---
        float m_dash_speed; // -> velocidad del dash
        float m_dash_cooldown; // -> tiempo cooldown para el dash
        float m_dash_cooldown_timer; // -> se usa para contar hacia atrás desde m_dash_cooldown
        
        float m_dash_duration; // -> duración del dash
        float m_dash_duration_timer; // -> para manejar duracion del dash actual

        bool m_can_dash;
        
        // --- WEAPONS ---
        Weapon* m_current_weapon;
        std::map<PlayerState, std::vector<Vector2>> m_weapon_anchor_points; // -> mapea estado de jugador a un vector de puntos de anclaje (uno para cada 
                                                                           // frame de la animacion)
        

    private:
        void setup_animations();
        void setup_weapon_anchor_points();

    public:
        Player(Vector2 position, Vector2 velocity, float scale);
        ~Player();

        void update() override;
        void render() override;
        void on_collision_with_floor(Rectangle floor) override;
        void on_collision_with_entity(Entity* entity) override;
        void on_collision_with_platform(Platform* platform) override;


        // ----------- ACCIONES DEL JUGADOR ----------
        void move(Vector2 direction) override;
        void stop_move() override;
        void jump();
        void dash();
        void stop_dash();
        
        Weapon* get_current_weapon() const;

        void equip_glock();
        void equip_ak47();
        


};










#endif
