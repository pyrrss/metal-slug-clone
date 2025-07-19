#include <iostream>

#include "raylib.h"

#include "TitleScreen.hpp"

TitleScreen::TitleScreen()
{
    // TODO: cargar cositas/recursos del menú principal acá
    
    // ------------ RECTANGULOS BOTONES ------------
    float button_width = 200.0f;
    float button_height = 50.0f;
    float button_spacing = 100.0f;
    
    m_play_button_rect.x = GetScreenWidth() / 2.0f - button_width / 2.0f;
    m_play_button_rect.y = GetScreenHeight() / 2.0f - button_height / 2.0f;
    m_play_button_rect.width = button_width;
    m_play_button_rect.height = button_height;

    
    m_options_button_rect.x = GetScreenWidth() / 2.0f - button_width / 2.0f;
    m_options_button_rect.y = GetScreenHeight() / 2.0f - button_height / 2.0f + button_spacing;
    m_options_button_rect.width = button_width;
    m_options_button_rect.height = button_height;


    m_exit_button_rect.x = GetScreenWidth() / 2.0f - button_width / 2.0f;
    m_exit_button_rect.y = GetScreenHeight() / 2.0f - button_height / 2.0f + button_spacing * 2;
    m_exit_button_rect.width = button_width;
    m_exit_button_rect.height = button_height;


}

TitleScreen::~TitleScreen()
{
    std::cout << "LOG: TitleScreen destruido" << std::endl;
}

void TitleScreen::init()
{

}

game_screen TitleScreen::update()
{
    // ------------ INTERACCIÓN BOTONES ----------
    if (CheckCollisionPointRec(GetMousePosition(), m_play_button_rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return game_screen::GAMEPLAY;
    }

    if (CheckCollisionPointRec(GetMousePosition(), m_options_button_rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return game_screen::OPTIONS;
    }

    if (CheckCollisionPointRec(GetMousePosition(), m_exit_button_rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return game_screen::GAMEPLAY;
    }



    // ------------ COLORES BOTONES -----------
    if (CheckCollisionPointRec(GetMousePosition(), m_play_button_rect))
    {
        m_play_button_color = RED;
    } 
    else 
    {
        m_play_button_color = DARKGRAY;
    }

    if (CheckCollisionPointRec(GetMousePosition(), m_options_button_rect))
    {
       m_options_button_color = RED;
    } 
    else 
    {
        m_options_button_color = DARKGRAY;
    }

    if (CheckCollisionPointRec(GetMousePosition(), m_exit_button_rect))
    {
        m_exit_button_color = RED;
    } 
    else 
    {
        m_exit_button_color = DARKGRAY;
    }


    return game_screen::NONE;
}

void TitleScreen::render()
{
    ClearBackground(GOLD);


    DrawText("ESTE ES EL MENÚ PRINCIPAL", 100, 200, 40, DARKGRAY);
    
    DrawRectangleRec(m_play_button_rect, m_play_button_color);
    DrawRectangleRec(m_options_button_rect, m_options_button_color);
    DrawRectangleRec(m_exit_button_rect, m_exit_button_color);

    // NOTE: MeasureText() mide cuanto ancho ocuparia un texto con cierto tamaño de fuente

    int font_size = 20;

    int play_button_text_width = MeasureText("a juga koma", font_size);

    DrawText(
        "a juga kompa",
        m_play_button_rect.x + m_play_button_rect.width / 2.0f - play_button_text_width / 2.0f,
        m_play_button_rect.y + m_play_button_rect.height / 2.0f - font_size / 2.0f,
        20, 
        BLACK
    );

    int options_button_text_width = MeasureText("ocppoone", 20);

    DrawText(
            "opcione",
            m_options_button_rect.x + m_options_button_rect.width / 2.0f - options_button_text_width / 2.0f,
            m_options_button_rect.y + m_options_button_rect.height / 2.0f - font_size / 2.0f,
            20, 
            BLACK
    );

    int exit_button_text_width = MeasureText("ocppoone", 20);

    DrawText(
            "a sali",
            m_exit_button_rect.x + m_exit_button_rect.width / 2.0f - exit_button_text_width / 2.0f,
            m_exit_button_rect.y + m_exit_button_rect.height / 2.0f - font_size / 2.0f,
            20, 
            BLACK
    );



}
