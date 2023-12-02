// Local
#include "macros.hpp"

// STD
#include <vector>
#include <memory>

// Godot
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>

// Poco
#include <Poco/UUID.h>

#pragma once

namespace godot {

    namespace weapons {

        class Weapon : public Area2D {
        protected:
            // Sprite and collision shape are present in every weapon.
            std::unique_ptr<godot::AnimatedSprite2D> m_weapon_sprite;
            std::unique_ptr<godot::CollisionShape2D> m_weapon_shape {};
            // Editor lock.
            bool m_editor {false};
            // ID
            Poco::UUID m_id;

        public:
            virtual Poco::UUID obj_id() = 0;
        };

        class Firearm : public Weapon {
        protected:

            enum class FiringMode : int {
                single = 0, burst, automatic, special
            };

            enum class Animation : int {
                reload = 0, removal, taking, shooting
            };

            Vector2 m_firing_point {};
            FiringMode m_firing_mode {};
            std::vector<FiringMode> m_firing_modes {};

        protected:
            bool m_animation_lock {};
            size_t m_animation_time {};

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
            // Base Locators
            const std::string c_weapon_shape    {"AK47Sprite"};
            const std::string c_weapon_sprite   {"AK47Shape"};
            const std::string c_ak47            {"AK47"};
            // Animation overloads.
            virtual void m_reload() final;
            virtual void m_shoot() final;
            virtual void m_get_gun() final;
            virtual void m_remove_gun() final;
            // ID
            virtual Poco::UUID obj_id() final
            { return m_id; }
        protected:
            // Binding
            static void _bind_methods();
        public:
            void _ready() override;
            void _physics_process(const double p_delta) override;
            AK47();
            ~AK47();
        };
    }

}
