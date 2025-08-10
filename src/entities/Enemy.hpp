#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <map>
#include <memory>

#include "raylib.h"

#include "Entity.hpp"
#include "../core/Animation.hpp"
#include "../core/AIStrategy.hpp"


// NOTE: EnemyState hace referencia al estado físico/visual del enemigo 
enum class EnemyState
{
    IDLE, 
    RUNNING,
    ATTACKING,
    HURT,
    DYING
};

// NOTE: AIState hace referencia al estado del enemigo en cuanto a su comportamiento
enum class AIState
{
    PATROLLING,
    CHASING,
    ATTACKING

    // ......
};

struct EnemyStats
{
    float enemy_max_health;
    float enemy_speed;
    float enemy_damage;
    int enemy_score_points; // -> puntos que da enemigo al morir
    float enemy_scale;
    float enemy_attack_range;
    float enemy_chase_range;

    std::map<EnemyState, Animation> enemy_animations;

};

class Enemy : public Entity
{
    private:
        const EnemyStats m_enemy_stats;
        
        EnemyState m_enemy_state;
        AIState m_ai_state;
        
        std::unique_ptr<AIStrategy> m_current_ai_strategy;

        // -> vars para controlar animaciones
        float m_frames_timer;
        int m_current_animation_frame;
        int m_facing_direction; // -> dirección donde se mira := 1 derecha, -1 izquierda, 0 vertical?
    
        Vector2 m_movement_direction;

    private:
        bool is_player_in_range(Player& player, float range);


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
        
        void update_ai(Player& player); // -> gestiona transiciones de estados de comportamiento
        void set_ai_strategy(std::unique_ptr<AIStrategy> ai_strategy);

};













#endif
