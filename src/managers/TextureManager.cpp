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

    // --------------- WEAPONS --------------
    Texture2D glock_idle_texture = LoadTexture("assets/weapons/glock/glock_idle.png");
    s_textures["glock_idle"] = glock_idle_texture;
    
    Texture2D glock_shooting_texture = LoadTexture("assets/weapons/glock/glock_shooting.png");
    s_textures["glock_shooting"] = glock_shooting_texture;

    Texture2D glock_bullet_texture = LoadTexture("assets/weapons/glock/glock_bullet.png");
    s_textures["glock_bullet"] = glock_bullet_texture;
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
}

Texture2D TextureManager::get_texture(const std::string& name)
{
    return s_textures[name];
}
