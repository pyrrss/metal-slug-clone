#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "raylib.h"

struct Animation
{
    Texture2D texture; // -> texture del spritesheet
    Rectangle* frames; // -> lista de frames del spritesheet
    int frame_count; // -> cantidad de frames del spritesheet
    int frame_speed; // -> velocidad de animación en frames por segundo (ej: 8)
    bool loops; // -> indica si animación debe repetirse o no
};




#endif
