// Local
#include "macros.hpp"

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

#pragma once

namespace godot {

    class Player : public godot::Area2D {
        // Godot wrapper for inheritance.
        GDCLASS(Player, godot::Area2D)

        const std::string c_collision_shape_name {"CollisionShape"};
        const std::string c_animated_sprite {"AnimatedSprite"};

        const std::string c_walking_right_animation {"walking_right"};
        const std::string c_walking_left_animation {"walking_left"};
        const std::string c_idle_animation {"idle"};

        godot::Input*                     m_input {};
        godot::Vector2                    m_screen_size {};
        std::unique_ptr<AnimatedSprite2D> m_animated_sprite {nullptr};
        std::unique_ptr<CollisionShape2D> m_collision_shape {nullptr};

        EXLIB_PROPERTY(real_t, speed, 400)

    protected:
        // Godot API to bind class members in game Editor.
        static void _bind_methods();

    public:
        void _init() {}
        void _ready() override;
        void _enter_tree() override;
        void _physics_process(const double p_delta) override;
        void start(const godot::Vector2 p_position);
        void _on_body_entered(std::unique_ptr<godot::Node2D> _body);

        ~Player();
    };

}
