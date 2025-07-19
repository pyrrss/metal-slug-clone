#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include "raylib.h"

#include "Screen.hpp"

class TitleScreen : public Screen
{
    private:
        Rectangle m_play_button_rect;
        Rectangle m_options_button_rect;
        Rectangle m_exit_button_rect;

        Color m_play_button_color;
        Color m_options_button_color;
        Color m_exit_button_color;

    public:
        TitleScreen();
        ~TitleScreen();

        void init() override;
        game_screen update() override;
        void render() override;


};











#endif
