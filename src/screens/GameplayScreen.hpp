#ifndef GAMEPLAY_SCREEN_HPP
#define GAMEPLAY_SCREEN_HPP

#include "Screen.hpp"

// NOTE: por ahora esta pantalla será la que se use para mostrar funcionalidades del juego
class GameplayScreen : public Screen
{
    private:


    public:
        GameplayScreen();
        ~GameplayScreen();

        void init() override;
        game_screen update() override;
        void render() override;

        
};

















#endif
