#include <iostream>

#include "raylib.h"

#include "Game.hpp"

#include "../screens/LogoScreen.hpp"
#include "../screens/TitleScreen.hpp"
#include "../screens/OptionsScreen.hpp"
#include "../screens/GameplayScreen.hpp"

#include "../managers/TextureManager.hpp"

Game::Game(int screen_width, int screen_height)
{
    // TODO: hacer que se pueda reajustar tamaño de la ventana (permitir pantalla completa?)

    this->m_screen_width = screen_width;
    this->m_screen_height = screen_height;
}

Game::~Game()
{
    // TODO: destruir todo
    
    std::cout << "LOG: Game destruido" << std::endl;

    TextureManager::unload_all_textures();
    CloseWindow();

}

void Game::run()
{
    // TODO: inicializar todo acá
    // -------------------------------------------------------------
    std::cout << "Game::init()" << std::endl;
 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(m_screen_width, m_screen_height, "Metal Slug Clone");
    SetTargetFPS(60);

    // -> CARGA DE ASSETS 
    TextureManager::load_all_textures();
    
    // -------------------------------------------------------------
    

    int frames_counter = 0; // -> contador de frames
    
    change_screen(game_screen::LOGO); // -> se muestra primero pantalla de logo
    game_screen next_screen = game_screen::NONE;

    // -> game-loop 
    while (!WindowShouldClose()) // NOTE: WindowShouldClose detecta si se ha pulsado ESC o botón para cerrar
    {
        // -> se muestra pantalla de logo por 2 segundos y luego se va a la pantalla de títutlo
        if (m_current_screen_type == game_screen::LOGO && frames_counter >= 180)
        {
            change_screen(game_screen::TITLE);
        }


        // TODO: Update cosas acá
        // --------------------------------------------------------------
        frames_counter++;

        // -> cambio de pantalla
        if (m_current_screen != nullptr)
        {
            next_screen = m_current_screen->update();
            
            if (next_screen != game_screen::NONE)
            {
                change_screen(next_screen);
            }

        }

        // --------------------------------------------------------------
    

        
        // ----------------------- RENDER -------------------------------
        // TODO: Render cosas acá (luego ver donde colocar esto o lo que sea)
        BeginDrawing();
        
        DrawFPS(10, 10);
        DrawText(TextFormat("Frames: %i", frames_counter), 10, 40, 20, BLACK);
        
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
        delete m_current_screen; // -> se borra pantalla actual (y se llama a su destructor)
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
            m_current_screen = new TitleScreen();
        } break;

        case game_screen::OPTIONS:
        {
            m_current_screen = new OptionsScreen();
        } break;

        case game_screen::GAMEPLAY:
        {
            m_current_screen = new GameplayScreen();
        } break;

        case game_screen::GAME_OVER:
        {
            m_current_screen = nullptr;
        } break;
        
        default: break;

    }
    
    m_current_screen->init();
    
}






