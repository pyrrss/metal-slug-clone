#ifndef SCREEN_HPP
#define SCREEN_HPP

enum class game_screen
{
    NONE, // -> esto es para indicar que no hay cambio a ninguna pantalla
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
        virtual void init() = 0; // -> NOTE: inicializar pantalla, capaz se puede hacer todo en el constructor y sacar este método?
        virtual game_screen update() = 0; // -> actualizar pantalla (devuelve siguiente estado al que se va a cambiar)
        virtual void render() = 0; // -> renderizar pantalla
        // virtual void de_init() = 0; // -> deinicializar pantalla

};







#endif
