#include <iostream>
#include <string>

#include "Game.hpp"
#include "raylib.h"


Game::Game(int screen_width, int screen_height)
{
    // TODO: hacer que se pueda reajustar tamaño de la ventana (permitir pantalla completa?)

    this->m_screen_width = screen_width;
    this->m_screen_height = screen_height;
}

Game::~Game()
{
    // TODO: destruir todo
    
    CloseWindow();
}

void Game::run()
{
    // TODO: inicializar todo acá
    // -------------------------------------------------------------
    std::cout << "Game::init()" << std::endl;
    
    InitWindow(m_screen_width, m_screen_height, "Metal Slug Clone");
    SetTargetFPS(60);
    
    // -------------------------------------------------------------
    

    int frames_counter = 0; // -> contador de frames
    
    change_screen(game_screen::LOGO); // -> se muestra primero pantalla de logo

    // -> game-loop // -> se muestra primero pantalla de logo
    while (!WindowShouldClose()) // NOTE: WindowShouldClose detetta si se ha pulsado ESC o botón para cerrar
    {
        frames_counter++;
        
        // -> se muestra pantalla de logo por 2 segundos y luego se va a la pantalla de títutlo
        // if (frames_counter >= 120)
        // {
        //     change_screen(game_screen::TITLE);
        // }


        // TODO: Update cosas acá
        // --------------------------------------------------------------


        // --------------------------------------------------------------
    

        
        // ----------------------- RENDER -------------------------------
        // TODO: Render cosas acá (luego ver donde colocar esto o lo que sea)
        BeginDrawing();
            
            ClearBackground(RAYWHITE);    
            
            DrawText("Game::run()", 200, 300, 40, LIGHTGRAY);

            DrawText(("Frames counter: " + std::to_string(frames_counter)).c_str(), 200, 350, 40, LIGHTGRAY);

            DrawFPS(10, 10);


            if (m_current_screen != nullptr)
            {
                m_current_screen->render();
            }
        
        EndDrawing();



    }

}

void Game::change_screen(game_screen screen_type)
{
    if (m_current_screen != nullptr)
    {
        m_current_screen->de_init();
        delete m_current_screen; // -> se borra pantalla actual
    }

    m_current_screen_type = screen_type;

    switch (screen_type)
    {
        case game_screen::LOGO:
        {
            m_current_screen = new LogoScreen();
        } break;

        case game_screen::TITLE:
        {
            m_current_screen = nullptr;
        } break;

        case game_screen::OPTIONS:
        {
            m_current_screen = nullptr;
        } break;

        case game_screen::GAMEPLAY:
        {
            m_current_screen = nullptr;
        } break;

        case game_screen::GAME_OVER:
        {
            m_current_screen = nullptr;
        } break;
        
        default: break;

    }
    
    m_current_screen->init();


}






