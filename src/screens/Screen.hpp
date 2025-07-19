#ifndef SCREEN_HPP
#define SCREEN_HPP

enum class game_screen
{
    LOGO,
    TITLE,
    OPTIONS,
    GAMEPLAY,
    GAME_OVER
};


class Screen
{
    public:
        virtual ~Screen() = default;

        virtual void init() = 0; // -> inicializar pantalla
        virtual void update() = 0; // -> actualizar pantalla
        virtual void render() = 0; // -> renderizar pantalla
        virtual void de_init() = 0; // -> deinicializar pantalla

};







#endif
