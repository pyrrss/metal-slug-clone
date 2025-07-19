#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <iostream>
#include <map>

#include "raylib.h"

class TextureManager
{
    private:
        static std::map<std::string, Texture2D> s_textures; // -> mapa de las texturas cargadas

    public:

        static void load_all_textures(); // -> carga todas las texturas
        
        static void unload_all_textures(); // -> libera todas las texturas cargadas
        static void unload_texture(const std::string& name); // -> libera una textura específica
        
        static Texture2D get_texture(const std::string& name); // -> devuelve una textura específica


};












#endif
