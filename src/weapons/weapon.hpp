// Local
#include "macros.hpp"
#include "exlib_base.hpp"

// STD
#include <vector>
#include <memory>

// Godot
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/animation_player.hpp>

// Poco
#include <Poco/UUID.h>

#pragma once

namespace godot {

    namespace weapons {

        class Weapon : public Area2D, public exlib::ExlibBase {
        protected:
            const std::string c_weapon_shape        {"Sprite"};
            const std::string c_weapon_sprite       {"Shape"};
            const std::string c_weapon_animation    {"Animation"};
            // Sprite and collision shape are present in every weapon.
            std::unique_ptr<godot::AnimatedSprite2D>    m_weapon_sprite {};
            std::unique_ptr<godot::CollisionShape2D>    m_weapon_shape {};
            std::unique_ptr<godot::AnimationPlayer>     m_weapon_animation {};
            Weapon();
            ~Weapon();
            void m_ready();
        };

        class Firearm : public Weapon {
        public:
            enum class FiringMode : int {
                single = 0, burst, automatic, special
            };

            enum class Animation : int {
                none = 0, reload, removal, taking, shooting
            };

        protected:
            Vector2 m_firing_point {};
            FiringMode m_firing_mode {};
            std::vector<FiringMode> m_firing_modes {};

            Animation m_current_animation {};
            bool m_animation_lock {};

            virtual void m_reload() = 0;
            virtual void m_shoot() = 0;
            virtual void m_get_gun() = 0;
            virtual void m_remove_gun() = 0;
        };

        class AK47 : public Firearm {
            GDCLASS(AK47, Firearm)
            // Stats.
            // Recoil affects how fast precision is lost over time.
            EXLIB_PROPERTY(real_t, recoil, 0.3f)
            // Fire rate - how fast a gun can shoot (delay between shots).
            EXLIB_PROPERTY(real_t, firerate, 0.3f)
            // Reload time.
            EXLIB_PROPERTY(real_t, reload, 1.5f)
            // Damage per shot.
            EXLIB_PROPERTY(real_t, damage, 10.0f)
            // Precision affects the cone which dictates shot spread.
            EXLIB_PROPERTY(real_t, precision, 10.0f);
            // Speed of individual bullet (or grenade).
            EXLIB_PROPERTY(real_t, shot_speed, 900.0f);
            std::vector<FiringMode> m_firing_modes
            {
                FiringMode::automatic,
                FiringMode::single
            };
            // Animation overloads.
            virtual void m_reload() final;
            virtual void m_shoot() final;
            virtual void m_get_gun() final;
            virtual void m_remove_gun() final;
            // Binding
            static void _bind_methods();
        public:
            void _ready() override;
            void _physics_process(const double p_delta) override;
        };
    }

}
