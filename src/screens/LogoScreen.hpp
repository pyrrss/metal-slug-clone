#ifndef LOGO_SCREEN_HPP
#define LOGO_SCREEN_HPP

#include "Screen.hpp"

class LogoScreen : public Screen
{
    public:
        LogoScreen();
        ~LogoScreen() = default;

        void init() override;
        void update() override;
        void render() override;
        void de_init() override;
};











#endif
