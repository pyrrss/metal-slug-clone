#include <iostream>

#include "core/Game.hpp"
#include "raylib.h"

enum class game_state
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
};


int main()
{
    std::cout << "Este será próximamente un clon de Metal Slug :)" << std::endl;
    
    Game game(800, 600);
    game.run();


    // // -> inicialización de ventana
    // InitWindow(screen_width, screen_height, "Metal Slug Clone");
    // SetTargetFPS(60);
    //
    // game_state current_state = game_state::LOGO;
    //
    // int frames_counter = 0; // -> contador de frames
    //
    // // -> game-loop
    // while (!WindowShouldClose()) // NOTE: WindowShouldClose detecta si se ha pulsado ESC o botón para cerrar
    // {
    //     // Update
    //     // --------------------------------------------------------------
    //     switch (current_state)
    //     {
    //         case game_state::LOGO:
    //         {
    //             // TODO: actualizar cosas del logo acá
    //
    //             frames_counter++;
    //
    //             if (frames_counter >= 120)
    //             {
    //                 current_state = game_state::TITLE;
    //             }
    //
    //
    //         } break;
    //
    //         case game_state::TITLE:
    //         {
    //             // TODO: actualizar cosas del titulo acá
    //
    //             if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //             {
    //                 current_state = game_state::GAMEPLAY;
    //             }
    //
    //         } break;
    // 
    //         case game_state::GAMEPLAY:
    //         {
    //             // TODO: actualizar cosas del juego acá
    //
    //             if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //             {
    //                 current_state = game_state::ENDING;
    //             }
    //         } break;
    //
    //         case game_state::ENDING:
    //         {
    //             // TODO: actualizar cosas del juego acá
    //
    //             if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //             {
    //                 current_state = game_state::TITLE;
    //             }
    //         } break;
    //
    //         default: break;
    //    }
    //
    //
    //     BeginDrawing();
    //
    //         ClearBackground(RAYWHITE);
    //         switch(current_state)
    //         {
    //             case game_state::LOGO:
    //                 {
    //                     // TODO: Draw LOGO screen here!
    //                     DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
    //                     DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
    //
    //                 } break;
    //             case game_state::TITLE:
    //                 {
    //                     // TODO: Draw TITLE screen here!
    //                     DrawRectangle(0, 0, screen_width, screen_height, GREEN);
    //                     DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
    //                     DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    //
    //                 } break;
    //             case game_state::GAMEPLAY:
    //                 {
    //                     // TODO: Draw GAMEPLAY screen here!
    //                     DrawRectangle(0, 0, screen_width, screen_height, PURPLE);
    //                     DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
    //                     DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    //
    //                 } break;
    //             case game_state::ENDING:
    //                 {
    //                     // TODO: Draw ENDING screen here!
    //                     DrawRectangle(0, 0, screen_width, screen_height, BLUE);
    //                     DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
    //                     DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
    //
    //                 } break;
    //             default: break;
    //         }
    //     EndDrawing();
    //
    // }
    //
    // CloseWindow(); // -> destruye ventana


}
