#include <iostream>
#include <raylib.h>

#include "TextureManager.hpp"

// -> se define el map de texturas (en el header se define como static)
std::map<std::string, Texture2D> TextureManager::s_textures;

void TextureManager::load_all_textures()
{
    // TODO: todas las texturas se cargan aquí y se guardan en el map
    

    Texture2D logo_texture = LoadTexture("assets/raylib_144x144.png");
    s_textures["logo"] = logo_texture;

    // SPRITES DE SAMURAI

    // Texture2D player_iddle_texture = LoadTexture("assets/player/IDLE.png");
    // s_textures["player_idle"] = player_iddle_texture;
    //
    // Texture2D player_running_texture = LoadTexture("assets/player/RUN.png");
    // s_textures["player_running"] = player_running_texture;

    // NOTE: NO HAY SPRITESHEET DE SALTO XD
    // Texture2D player_jumping_texture = LoadTexture("assets/player/JUMP.png");

    // SPRITES DE WARRIOR
    Texture2D player_idle_texture = LoadTexture("assets/player/IDLE2.png");
    s_textures["player_idle"] = player_idle_texture;

    Texture2D player_running_texture = LoadTexture("assets/player/RUN2.png");
    s_textures["player_running"] = player_running_texture;

    Texture2D player_jumping_texture = LoadTexture("assets/player/JUMP2.png");
    s_textures["player_jumping"] = player_jumping_texture;
 
    Texture2D player_dashing_texture = LoadTexture("assets/player/DASH.png");
    s_textures["player_dashing"] = player_dashing_texture;

}

void TextureManager::unload_all_textures()
{
    // TODO: todas las texturas se liberan aquí

    UnloadTexture(s_textures["logo"]);
    UnloadTexture(s_textures["player_idle"]);
    UnloadTexture(s_textures["player_running"]);
    UnloadTexture(s_textures["player_jumping"]);
}

Texture2D TextureManager::get_texture(const std::string& name)
{
    return s_textures[name];
}
