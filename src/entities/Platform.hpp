#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "GameObject.hpp"

class Platform : public GameObject
{
    public:
        Platform(Vector2 position, float width, float height);
        ~Platform();

        void render() override;
};

#endif