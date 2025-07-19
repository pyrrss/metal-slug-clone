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


}

void TextureManager::unload_all_textures()
{
    // TODO: todas las texturas se liberan aquí

    UnloadTexture(s_textures["logo"]);
}

Texture2D TextureManager::get_texture(const std::string& name)
{
    return s_textures[name];
}
