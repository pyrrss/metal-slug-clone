#ifndef GAMEPLAY_SCREEN_HPP
#define GAMEPLAY_SCREEN_HPP

#include <vector>
#include <memory>

#include "../entities/Entity.hpp"
#include "Screen.hpp"

// NOTE: por ahora esta pantalla será la que se use para mostrar funcionalidades del juego
#include "../entities/Player.hpp"
#include "../entities/Platform.hpp"

class GameplayScreen : public Screen
{
    private:

        Rectangle m_floor;
        std::vector<Entity*> m_entities;
        std::vector<Platform*> m_platforms;

    public:
        GameplayScreen();
        ~GameplayScreen();

        void init() override;
        game_screen update() override;
        void render() override;

        
};

















#endif
