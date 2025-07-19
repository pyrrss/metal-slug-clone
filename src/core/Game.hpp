#ifndef GAME_HPP
#define GAME_HPP

#include "../screens/Screen.hpp"

class Game
{
    private: // -> atributos privados
        
        // TODO: crear funcionalidad para ajustar tamaño de pantalla
        int m_screen_width;
        int m_screen_height;
    
        Screen* m_current_screen = nullptr;
        game_screen m_current_screen_type;

    private: // -> métodos privados


    public:
        Game(int screen_width, int screen_height);
        ~Game();
        
        void run(); // -> inicializa y ejecuta el juego
        
        void change_screen(game_screen screen_type);
};










#endif
