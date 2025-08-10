#ifndef GAMEPLAY_SCREEN_HPP
#define GAMEPLAY_SCREEN_HPP

#include <vector>
#include <memory>

#include "../entities/Enemy.hpp"
#include "Screen.hpp"

// NOTE: por ahora esta pantalla será la que se use para mostrar funcionalidades del juego
#include "../entities/Player.hpp"
#include "../entities/Platform.hpp"

#include "../core/ParallaxLayer.hpp"

class GameplayScreen : public Screen
{
    private:

        Rectangle m_floor;
 
        Camera2D m_camera;

        std::unique_ptr<Player> m_player;
        std::vector<std::unique_ptr<Enemy>> m_enemies;
        std::vector<std::unique_ptr<Platform>> m_platforms;
        std::vector<std::unique_ptr<Bullet>> m_bullets;

        std::vector<ParallaxLayer> m_parallax_layers;

    public:
        GameplayScreen();
        ~GameplayScreen();

        void init() override;
        game_screen update() override;
        void render() override;

        
};

















#endif
