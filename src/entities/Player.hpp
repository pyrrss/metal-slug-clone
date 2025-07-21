#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>

#include "raylib.h"

#include "Entity.hpp"
#include "../core/Animation.hpp"

enum class PlayerState
{
    IDLE,
    RUNNING,
    JUMPING,
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

        float m_scale;
        
        PlayerState m_player_state;
        std::map<PlayerState, Animation> m_animations; // -> mapea estado de jugador a una animación
        

    private:
        void setup_animations();


    public:
        Player(Vector2 position, Vector2 size, Vector2 velocity, float scale);
        ~Player();

        void update() override;
        void render() override;

        // ----------- ACCIONES DEL JUGADOR ----------
        void move(Vector2 direction);
        void stop_move();
        void jump();

};










#endif
