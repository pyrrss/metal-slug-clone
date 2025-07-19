#include <iostream>
#include <raylib.h>

#include "LogoScreen.hpp"
#include "../managers/TextureManager.hpp"


LogoScreen::LogoScreen()
{
    // TODO: cargar logo acá
    // this->m_logo_texture = LoadTexture("../../assets/logo.png");

}

LogoScreen::~LogoScreen()
{
    std::cout << "LOG: LogoScreen destruido" << std::endl;
    // UnloadTexture(this->m_logo_texture);
}

void LogoScreen::init()
{
    
}

game_screen LogoScreen::update()
{
    return game_screen::NONE;
}

void LogoScreen::render()
{
    // TODO: Dibujar logo del juego acá
    
    ClearBackground(RAYWHITE);

    DrawTexture(TextureManager::get_texture("logo"), 0, 0, WHITE);
    
    DrawText("Metal Slug Clone compa", (GetScreenWidth() / 2) - 180, (GetScreenHeight() / 2), 30, LIGHTGRAY);

}

