// Local
#include "macros.hpp"

// STD
#include <vector>
#include <memory>

// Godot
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {

    enum class Weapons : int {
        firearm = 0
    };

    enum class Firearms : int {
        ak_47_rifle = 0, m_16_rifle, luger_pistol
    };

    enum class FiringMode : int {
        single = 0, burst, automatic, special
    };

    class Firearm : Area2D {
        GDCLASS(Firearm, Area2D)

        Vector2 m_firing_point {};
        FiringMode m_firing_mode {};
        std::vector<FiringMode> m_firing_modes {};
        std::unique_ptr<godot::AnimatedSprite2D> m_animated_sprite {};
        std::unique_ptr<godot::CollisionShape2D> m_collision_shape {};

        EXLIB_PROPERTY(double, recoil, 0)
        EXLIB_PROPERTY(double, firerate, 20)
        EXLIB_PROPERTY(double, reload, 5)
        EXLIB_PROPERTY(double, damage, 10)
        EXLIB_PROPERTY(double, presicion, 5);
        EXLIB_PROPERTY(double, shot_speed, 800);

        virtual void m_reload();
        virtual void m_shoot();
        virtual void m_get_gun();
        virtual void m_remove_gun();

    protected:
        static void _bind_methods();
    };

}
