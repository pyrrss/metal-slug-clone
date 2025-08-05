#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <map>
#include <string>
#include <memory>

#include "raylib.h"

#include "GameObject.hpp"
#include "../core/Animation.hpp"

enum class WeaponState
{
    IDLE,
    SHOOTING,
    RELOADING
};

struct Bullet : public GameObject
{
    private:
        Texture2D m_bullet_texture;
        float m_bullet_speed; // -> velocidad en frames por segundo
        int m_bullet_max_distance;
        int m_bullet_current_distance;
        bool m_is_active;
        int m_facing_direction; // -> La bala ahora recuerda su propia dirección
    
        float m_bullet_scale;
        
        Rectangle m_source_rec;
    public:
        Bullet(Vector2 position, int facing_direction); // -> El constructor ahora acepta una dirección
        ~Bullet() = default;

        void update() override;
        void render() override;
        bool is_active() const;

};



// NOTE: para el sistema de armas, se usará un enfoque OO con composición, esto es,
// Weapon constituye la clase base y principal (con sus características y comportamientos comunes a todas las armas)
// y para cada tipo de arma se crea un WeaponStats con solamente sus datos específicos, para luego componerla con Weapon
// e inyectar todos sus datos

struct WeaponStats
{
    std::string weapon_name;
    int weapon_damage;
    float weapon_scale;
    // ......
    

    std::map<WeaponState, Animation> weapon_animations;

};




class Weapon : public GameObject
{
    private:

        // NOTE: Weapon almacena cualquier dato que sea dinámico, referente al estado actual del arma,
        // mientras que WeaponStats almacena datos estáticos; nombre, daño,...

        WeaponState m_weapon_state;
    
        const WeaponStats m_weapon_stats;
        
        // -> vars para controlar animaciones
        float m_frames_timer;
        int m_current_animation_frame;
        int m_facing_direction; // -> dirección donde se mira := 1 derecha, -1 izquierda, 0 vertical?


    public:
        Weapon(Vector2 position, const WeaponStats& stats);
        ~Weapon() = default;
        
        void update() override;
        void render() override;
        
        void update_transform(Vector2 position, int facing_direction);

        std::unique_ptr<Bullet> shoot();

};













#endif
