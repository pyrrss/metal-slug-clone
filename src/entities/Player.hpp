#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"

#include "Entity.hpp"

class Player : public Entity
{
    private:
        Texture2D m_idle_texture;
        Rectangle m_idle_frames[10]; 
        int m_idle_frames_count;
        int m_frames_counter;
        int m_current_frame;
        int m_frames_speed;
        float m_scale;


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
