#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <map>

#include "raylib.h"

#include "Entity.hpp"
#include "../core/Animation.hpp"

enum class EnemyState
{
    SPAWNING,
    IDLE, 
    RUNNING,
    ATTACKING,
    HURT,
    DYING
};

struct EnemyStats
{
    float enemy_max_health;
    float enemy_speed;
    float enemy_damage;
    int enemy_score_points; // -> puntos que da enemigo al morir
    float enemy_scale;
    // ......


    std::map<EnemyState, Animation> enemy_animations;

};




class Enemy : public Entity
{
    private:
        const EnemyStats m_enemy_stats;
        
        EnemyState m_enemy_state;

        // -> vars para controlar animaciones
        float m_frames_timer;
        int m_current_animation_frame;
        int m_facing_direction; // -> dirección donde se mira := 1 derecha, -1 izquierda, 0 vertical?
    
        Vector2 m_movement_direction;

    public:
        Enemy(Vector2 position, Vector2 velocity, const EnemyStats& stats);
        ~Enemy() = default;
            
        void update() override;
        void render() override;
    

        void on_collision_with_floor(Rectangle floor) override;
        void on_collision_with_entity(Entity* entity) override;
        void on_collision_with_platform(Platform* platform) override;

        // --- ACCIONES ---
        void move(Vector2 direction) override;
        void stop_move() override;
        void attack();
        void die();        


};













#endif
