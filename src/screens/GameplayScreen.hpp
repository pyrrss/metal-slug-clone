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
        std::vector<std::unique_ptr<Entity>> m_entities;
        std::vector<std::unique_ptr<Platform>> m_platforms;
        std::vector<std::unique_ptr<Bullet>> m_bullets;


    public:
        GameplayScreen();
        ~GameplayScreen();

        void init() override;
        game_screen update() override;
        void render() override;

        
};

















#endif
