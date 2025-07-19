#ifndef LOGO_SCREEN_HPP
#define LOGO_SCREEN_HPP

#include "Screen.hpp"
#include "raylib.h"

class LogoScreen : public Screen
{
    private:
        Texture2D m_logo_texture;

    public:
        LogoScreen();
        ~LogoScreen();

        void init() override;
        game_screen update() override;
        void render() override;
};











#endif
