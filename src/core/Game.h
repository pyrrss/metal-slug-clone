#ifndef GAME_HPP
#define GAME_HPP

class Game
{
    private: // -> atributos privados
        int m_screen_width;
        int m_screen_height;
    
    private: // -> métodos privados
    // TODO: métodos privados


    public:
        Game(int screen_width, int screen_height);
        ~Game();
        
        void run(); // -> inicializa y ejecuta el juego

};










#endif
