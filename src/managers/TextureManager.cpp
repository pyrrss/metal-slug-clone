#include <iostream>
#include <raylib.h>

#include "TextureManager.hpp"

// -> se define el map de texturas (en el header se define como static)
std::map<std::string, Texture2D> TextureManager::s_textures;

void TextureManager::load_all_textures()
{
    // NOTE: todas las texturas se cargan aquí y se guardan en el map
    

    Texture2D logo_texture = LoadTexture("assets/raylib_144x144.png");
    s_textures["logo"] = logo_texture;


    // --------------- PLAYER ---------------
    Texture2D player_idle_texture = LoadTexture("assets/player/IDLE2.png");
    s_textures["player_idle"] = player_idle_texture;

    Texture2D player_running_texture = LoadTexture("assets/player/RUN2.png");
    s_textures["player_running"] = player_running_texture;

    Texture2D player_jumping_texture = LoadTexture("assets/player/JUMP2.png");
    s_textures["player_jumping"] = player_jumping_texture;
 
    Texture2D player_dashing_texture = LoadTexture("assets/player/DASH.png");
    s_textures["player_dashing"] = player_dashing_texture;

    Texture2D player_attacking_texture = LoadTexture("assets/player/ATTACK.png");
    s_textures["player_attacking"] = player_attacking_texture;

    // --------------- WEAPONS --------------
    Texture2D glock_idle_texture = LoadTexture("assets/weapons/glock/glock_idle.png");
    s_textures["glock_idle"] = glock_idle_texture;
    
    Texture2D glock_shooting_texture = LoadTexture("assets/weapons/glock/glock_shooting.png");
    s_textures["glock_shooting"] = glock_shooting_texture;

    Texture2D glock_bullet_texture = LoadTexture("assets/weapons/glock/glock_bullet.png");
    s_textures["glock_bullet"] = glock_bullet_texture;

    


    // --------------- ENEMIES --------------
    
    // NOTE: todas las texturas y animaciones de skeleton estan en el mismo spritesheet
    Texture2D skeleton_texture = LoadTexture("assets/enemies/skeleton/skeleton_enemy.png");
    s_textures["skeleton"] = skeleton_texture;


    // --------------- PARALLAX LAYERS BACKGROUND --------------
    
    Texture2D layer1_bg_texture = LoadTexture("assets/backgrounds/mountain/layer1.png");
    s_textures["layer1_bg"] = layer1_bg_texture;

    Texture2D layer2_bg_texture = LoadTexture("assets/backgrounds/mountain/layer2.png");
    s_textures["layer2_bg"] = layer2_bg_texture;
    
    Texture2D layer3_bg_texture = LoadTexture("assets/backgrounds/mountain/layer3.png");
    s_textures["layer3_bg"] = layer3_bg_texture;

    Texture2D layer4_bg_texture = LoadTexture("assets/backgrounds/mountain/layer4.png");
    s_textures["layer4_bg"] = layer4_bg_texture;

    Texture2D layer5_bg_texture = LoadTexture("assets/backgrounds/mountain/layer5.png");
    s_textures["layer5_bg"] = layer5_bg_texture;

    Texture2D layer6_bg_texture = LoadTexture("assets/backgrounds/mountain/layer6.png");
    s_textures["layer6_bg"] = layer6_bg_texture;
}

void TextureManager::unload_all_textures()
{
    // NOTE: se borran todas las texturas cargadas

    UnloadTexture(s_textures["logo"]);
    UnloadTexture(s_textures["player_idle"]);
    UnloadTexture(s_textures["player_running"]);
    UnloadTexture(s_textures["player_jumping"]);
    UnloadTexture(s_textures["player_dashing"]);
    UnloadTexture(s_textures["glock_idle"]);
    UnloadTexture(s_textures["glock_shooting"]);
    UnloadTexture(s_textures["glock_bullet"]);
    UnloadTexture(s_textures["skeleton"]);
    UnloadTexture(s_textures["layer1_bg"]);
    UnloadTexture(s_textures["layer2_bg"]);
    UnloadTexture(s_textures["layer3_bg"]);
    UnloadTexture(s_textures["layer4_bg"]);
    UnloadTexture(s_textures["layer5_bg"]);
    UnloadTexture(s_textures["layer6_bg"]);
}

Texture2D TextureManager::get_texture(const std::string& name)
{
    return s_textures[name];
}
