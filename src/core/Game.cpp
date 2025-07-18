#include <iostream>
#include <string>

#include "Game.h"
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
    
    // -> game-loop
    while (!WindowShouldClose()) // NOTE: WindowShouldClose detetta si se ha pulsado ESC o botón para cerrar
    {
        // TODO: Update cosas acá
        // --------------------------------------------------------------
        frames_counter++;


        // --------------------------------------------------------------
    

        // TODO: Render cosas acá (luego ver donde colocar esto o lo que sea)
        BeginDrawing();
            
            ClearBackground(RAYWHITE);    
            
            DrawText("Game::run()", 200, 300, 40, LIGHTGRAY);

            DrawText(("Frames counter: " + std::to_string(frames_counter)).c_str(), 200, 350, 40, LIGHTGRAY);

            DrawFPS(10, 10);
        
        EndDrawing();





    }

}
