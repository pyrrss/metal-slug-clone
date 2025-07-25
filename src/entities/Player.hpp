#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>

#include "raylib.h"

#include "Entity.hpp"
#include "../core/Animation.hpp"
#include "Platform.hpp"

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
        int m_frames_speed;
        int m_current_animation_frame;
        int m_facing_direction; // -> dirección donde se mira := 1 derecha, -1 izquierda, 0 vertical?
        
        PlayerState m_player_state;
        std::map<PlayerState, Animation> m_animations; // -> mapea estado de jugador a una animación
        
        float m_scale;

        Vector2 m_movement_direction;

        // --- Dash ---
        bool m_can_dash;
        float m_dash_duration;
        float m_dash_timer;
        float m_dash_speed;
        float m_dash_cooldown;
        float m_dash_cooldown_timer;


    private:
        void setup_animations();


    public:
        Player(Vector2 position, Vector2 velocity, float scale);
        ~Player();

        void update() override;
        void render() override;
        void on_collision_with_floor(Rectangle floor) override;
        void on_collision_with_entity(Entity* entity) override;
        void on_collision_with_platform(Platform* platform) override;


        // ----------- ACCIONES DEL JUGADOR ----------
        void move(Vector2 direction);
        void stop_move();
        void jump();
        void dash();
        void stop_dash();
};










#endif
