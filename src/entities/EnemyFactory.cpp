#include "EnemyFactory.hpp"

#include "../managers/TextureManager.hpp"

namespace EnemyFactory
{
    EnemyStats create_skeleton_stats()
    {
        EnemyStats skeleton_stats;

        // TODO: revisar y ajustar/equilibrar stats luego
        skeleton_stats.enemy_max_health = 100.0f;
        skeleton_stats.enemy_speed = 250.0f;
        skeleton_stats.enemy_damage = 10.0f;
        skeleton_stats.enemy_score_points = 10;
        skeleton_stats.enemy_scale = 4.0f;
        skeleton_stats.enemy_attack_range = 150.0f;
        skeleton_stats.enemy_chase_range = 400.0f;

        // ------------- ANIMACIONES ------------
        
        // --- HURT ---
        Animation hurt_animation;
        hurt_animation.texture = TextureManager::get_texture("skeleton");
        hurt_animation.frame_count = 3;
        hurt_animation.frame_speed = 5;
        hurt_animation.loops = false;
        hurt_animation.frames =
        {
            { 9, 271, 32, 33 },
            { 73, 272, 32, 33 },
            { 137, 272, 32, 33 }
        };

        skeleton_stats.enemy_animations[EnemyState::HURT] = hurt_animation;
    

        // --- IDLE ---
        Animation idle_animation;
        idle_animation.texture = TextureManager::get_texture("skeleton");
        idle_animation.frame_count = 4;
        idle_animation.frame_speed = 10;
        idle_animation.loops = true;
        idle_animation.frames =
        {
            { 9, 208, 33, 33 },
            { 73, 209, 34, 32 },
            { 137, 209, 35, 32 },
            { 201, 208, 34, 32 }
        };
        
        skeleton_stats.enemy_animations[EnemyState::IDLE] = idle_animation;

        // TODO: hacer resto de animaciones de SKELETON
        
        // --- RUNNING ---
        Animation running_animation;
        running_animation.texture = TextureManager::get_texture("skeleton");
        running_animation.frame_count = 12;
        running_animation.frame_speed = 10;
        running_animation.loops = true;
        running_animation.frames =
        {
            { 5, 145, 36, 31 },
            { 70, 144, 35, 32 },
            { 134, 144, 35, 32 },
            { 198, 144, 35, 32 },
            { 261, 145, 36, 31 },
            { 325, 146, 36, 30 },
            { 389, 145, 36, 31 },
            { 452, 144, 38, 32 },
            { 516, 144, 38, 32 },
            { 580, 144, 38, 32 },
            { 645, 145, 37, 31 },
            { 709, 146, 37, 30 }
        };
        
        skeleton_stats.enemy_animations[EnemyState::RUNNING] = running_animation;

        // --- ATTACKING ---
        Animation attacking_animation;
        attacking_animation.texture = TextureManager::get_texture("skeleton");
        attacking_animation.frame_count = 13;
        attacking_animation.frame_speed = 10;
        attacking_animation.loops = false;
        attacking_animation.frames = 
        {
            { 8, 16, 34, 32 },
            { 69, 16, 37, 32 },
            { 129, 16, 41, 32 },
            { 196, 16, 38, 32 },
            { 269, 8, 51, 40 },
            { 335, 9, 31, 39 },
            { 401, 15, 26, 33 },
            { 466, 15, 25, 33 },
            { 514, 16, 62, 32 },
            { 579, 15, 39, 33 },
            { 646, 12, 36, 36 },
            { 706, 16, 40, 32 },
            { 776, 16, 34, 32 }
        };

        skeleton_stats.enemy_animations[EnemyState::ATTACKING] = attacking_animation;

        // --- DYING ---
        Animation dying_animation;
        dying_animation.texture = TextureManager::get_texture("skeleton");
        dying_animation.frame_count = 13;
        dying_animation.frame_speed = 10;
        dying_animation.loops = false;
        dying_animation.frames =
        {
            { 9, 79, 32, 33 },
            { 73, 80, 32, 32 },
            { 137, 81, 31, 31 },
            { 201, 84, 35, 28 },
            { 265, 83, 37, 29 },
            { 329, 82, 38, 30 },
            { 393, 80, 42, 32 },
            { 457, 79, 42, 33 },
            { 521, 79, 42, 33 },
            { 585, 79, 42, 33 },
            { 649, 80, 42, 32 },
            { 713, 82, 42, 30 },
            { 777, 105, 42, 7 }
        };

        skeleton_stats.enemy_animations[EnemyState::DYING] = dying_animation;
        

        return skeleton_stats;
    };







}
