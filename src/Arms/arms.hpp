// Local
#include "macros.hpp"

// STD headers.
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

// Logging
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

// Godot headers.
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

    enum class RelativeRot : int {
        left = 0, aligned, right
    };

    class Arms : public Area2D {
        GDCLASS(Arms, Area2D)

        std::unique_ptr<godot::AnimatedSprite2D> m_animated_sprite {};
        std::unique_ptr<godot::CollisionShape2D> m_collision_shape {};
        std::unique_ptr<godot::Input> m_input {};
        bool m_editor {false};

        const double c_proximity_delta = 1.0;

        const std::string c_collision_shape {"Shape"};
        const std::string c_animated_sprite {"AnimatedSprite"};

        // Weapons
        const std::string c_auto_rifle_ak_47 {"AK47"};
        const std::string c_auto_rifle_m15 {"M15"};
        const std::string c_pistol_luger {"Luger"};

        std::vector<std::string> m_sling {};

        double get_rotation_angle(godot::Vector2 base, godot::Vector2 target);

        EXLIB_PROPERTY_ENUM(RelativeRot, sprite_rotation, RelativeRot::right)

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _physics_process(const double delta) override;
        Arms();
        ~Arms();
    };
}
