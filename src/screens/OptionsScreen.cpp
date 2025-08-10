#include <iostream>

#include "raylib.h"

#include "OptionsScreen.hpp"

OptionsScreen::OptionsScreen()
{

}

OptionsScreen::~OptionsScreen()
{
    std::cout << "LOG: OptionsScreen destruido" << std::endl;
}

void OptionsScreen::init()
{

}

game_screen OptionsScreen::update()
{
    if (IsKeyPressed(KEY_Q))
    {
        return game_screen::TITLE;
    }



    return game_screen::NONE;
}

void OptionsScreen::render()
{
    ClearBackground(RAYWHITE);
    
    int font_size = 30;
    int font_width = MeasureText("Esta es la pantalla de opciones", font_size);

    DrawText(
            "Esta es la pantalla de opciones", 
            GetScreenWidth() / 2 - font_width / 2,
            GetScreenHeight() / 2 - font_size / 2,
            font_size,
            LIGHTGRAY
            
     );

}
