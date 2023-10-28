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

#pragma once

namespace godot {

    class Player : public godot::Area2D {
        // Godot wrapper for inheritance.
        GDCLASS(Player, godot::Area2D)

        godot::AnimatedSprite2D* m_animated_sprite {};
        godot::CollisionShape2D* m_collision_shape {};
        godot::Input*            m_input {};
        godot::Vector2           m_screen_size {};

        LIB_PROPERTY(real_t, speed, 400)

    protected:
        // Godot API to bind class members in game Editor.
        static void _bind_methods();

    public:
        void _init() {}
        void _ready() override;
        void _process(const double p_delta) override;
        void start(const godot::Vector2 p_position);
        void _on_body_entered(std::unique_ptr<godot::Node2D> _body);
    };

}
