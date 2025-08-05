#include "EnemyFactory.hpp"

#include "../managers/TextureManager.hpp"

namespace EnemyFactory
{
    EnemyStats create_skeleton_stats()
    {
        EnemyStats skeleton_stats;

        // TODO: revisar y ajustar/equilibrar stats luego
        skeleton_stats.enemy_max_health = 100.0f;
        skeleton_stats.enemy_speed = 20.0f;
        skeleton_stats.enemy_damage = 10.0f;
        skeleton_stats.enemy_score_points = 10;
        skeleton_stats.enemy_scale = 4.0f;

        // ------------- ANIMACIONES ------------
        
        // --- SPAWNING ---
        Animation spawning_animation;
        spawning_animation.texture = TextureManager::get_texture("skeleton");
        spawning_animation.frame_count = 3;
        spawning_animation.frame_speed = 5;
        spawning_animation.loops = false;
        spawning_animation.frames =
        {
            { 9, 271, 32, 33 },
            { 73, 272, 32, 33 },
            { 137, 272, 32, 33 }
        };

        skeleton_stats.enemy_animations[EnemyState::SPAWNING] = spawning_animation;
    

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

        return skeleton_stats;
    };







}
