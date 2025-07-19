#include <iostream>
#include <raylib.h>

#include "LogoScreen.hpp"

LogoScreen::LogoScreen()
{


}

void LogoScreen::init()
{

}

void LogoScreen::update()
{

}

void LogoScreen::render()
{
    // TODO: Dibujar logo del juego acá
    
    ClearBackground(RAYWHITE);

    DrawText("AQUÍ DEBERÍA IR UN LOGO", 100, 200, 40, LIGHTGRAY);
    
}

void LogoScreen::de_init()
{

}
