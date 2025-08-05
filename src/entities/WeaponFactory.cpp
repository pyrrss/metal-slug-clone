#include "WeaponFactory.hpp"

#include "../managers/TextureManager.hpp"

namespace WeaponFactory
{
    WeaponStats create_glock_stats()
    {
        WeaponStats glock_stats;
        glock_stats.weapon_name = "glock";
        glock_stats.weapon_damage = 10;
        glock_stats.weapon_scale = 2.0f;

        // ------------- ANIMACIONES ------------

        // --- IDLE ---
        Animation idle_animation;
        idle_animation.texture = TextureManager::get_texture("glock_idle");
        idle_animation.frame_count = 1;
        idle_animation.frame_speed = 1;
        idle_animation.loops = false;
        idle_animation.frames = 
        {
            { 18, 8, 30, 20 }
        };

        glock_stats.weapon_animations[WeaponState::IDLE] = idle_animation;
    
        // TODO: hacer resto de animaciones
        
        // -- SHOOTING --
        Animation shooting_animation;
        shooting_animation.texture = TextureManager::get_texture("glock_shooting");
        shooting_animation.frame_count = 12;
        shooting_animation.frame_speed = 30;
        shooting_animation.loops = false;
        shooting_animation.frames =
        {
            { 18, 8, 30, 20 },
            { 82, 8, 30, 20 },
            { 145, 6, 37, 22 },
            { 209, 4, 38, 24 },
            { 272, 1, 39, 27 },
            { 336, 4, 31, 24 },
            { 401, 1, 30, 27 },
            { 466, 5, 30, 23 },
            { 530, 8, 30, 20 },
            { 594, 8, 30, 20 },
            { 658, 8, 30, 20 },
            { 722, 8, 30, 24 }
        };
    
        glock_stats.weapon_animations[WeaponState::SHOOTING] = shooting_animation;

        return glock_stats;
    };

    WeaponStats create_ak47_stats()
    {
        WeaponStats ak47_stats;
        ak47_stats.weapon_name = "ak47";
        ak47_stats.weapon_damage = 30;
        ak47_stats.weapon_scale = 4.0f;

        // ------------- ANIMACIONES ------------

        // --- IDLE ---
        Animation idle_animation;
        idle_animation.texture = TextureManager::get_texture("ak47_idle"); // Asumo que la textura se llama así
        idle_animation.frame_count = 1;
        idle_animation.frame_speed = 1;
        idle_animation.loops = false;
        idle_animation.frames = 
        {
            { 0, 0, 50, 20 } // RECUERDA CAMBIAR ESTO por el rectángulo correcto del spritesheet
        };

        ak47_stats.weapon_animations[WeaponState::IDLE] = idle_animation;

        return ak47_stats;
    }


















}
