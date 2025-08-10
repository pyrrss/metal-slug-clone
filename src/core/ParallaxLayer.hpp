#ifndef PARALLAX_LAYER_HPP
#define PARALLAX_LAYER_HPP

#include "raylib.h"

struct ParallaxLayer
{
    Texture2D texture;
    Vector2 position;
    float scroll_speed; // -> factor de velocidad al que se mueve la capa del parallax
};

#endif
