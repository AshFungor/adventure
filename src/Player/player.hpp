// Local
#include "macros.hpp"
#include "Arms/arms.hpp"
#include "exlib_base.hpp"

// STD headers.
#include <memory>
#include <algorithm>
#include <iostream>

// Godot headers.
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/engine.hpp>

#pragma once

namespace godot {

    class Player : public godot::Area2D, public exlib::ExlibBase {
        // Godot wrapper for inheritance.
        GDCLASS(Player, godot::Area2D)

        const std::string c_collision_shape {"CollisionShape"};
        const std::string c_animated_sprite {"AnimatedSprite"};
        const std::string c_arms            {"Arms"};

        const std::string c_walking_right_animation {"walking_right"};
        const std::string c_walking_left_animation {"walking_left"};
        const std::string c_idle_animation {"idle"};
        const std::string c_walking_right_backwards_animation {"walking_right_backwards"};
        const std::string c_walking_left_backwards_animation {"walking_left_backwards"};

        std::unique_ptr<godot::Input> m_input {};
        godot::Vector2 m_screen_size {};
        std::unique_ptr<godot::AnimatedSprite2D> m_animated_sprite {nullptr};
        std::unique_ptr<godot::CollisionShape2D> m_collision_shape {nullptr};
        std::unique_ptr<godot::Arms> m_arms {};

        EXLIB_PROPERTY(real_t, speed, 400)

    protected:
        // Godot API to bind class members in game Editor.
        static void _bind_methods();

    public:
        void _init() {}
        void _ready() override;
        void _physics_process(const double p_delta) override;
        void start(const godot::Vector2 p_position);
        void _on_body_entered(std::unique_ptr<godot::Node2D> _body);
        Player();
        ~Player();
    };

}
