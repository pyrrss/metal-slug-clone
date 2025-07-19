#ifndef OPTIONS_SCREEN_HPP
#define OPTIONS_SCREEN_HPP

#include "Screen.hpp"


class OptionsScreen : public Screen
{
    public:
        OptionsScreen();
        ~OptionsScreen();

        game_screen update() override;
        void render() override;
        void init() override;




};











#endif
