#pragma once

// Local
#include <src/base.hpp>
#include <src/macros.hpp>

// STD headers.
#include <cmath>
#include <vector>

// Logging
// #include <plog/Log.h>
// #include <plog/Initializers/RollingFileInitializer.h>

// Godot headers.
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>


namespace exlib {

    enum class RelativeRot : int {
        left = 0, aligned, right
    };

    class Gun {
        // Empty for now
    };

    class Arms 
        : public godot::Area2D
        , public exlib::Base<false, true> {
        
        GDCLASS(Arms, godot::Area2D)

    public:
        Arms();

        void _ready() override;
        void _physics_process(const double delta) override;

    protected:
        static void _bind_methods();
    
    private:
        double get_rotation_angle(godot::Vector2 base, godot::Vector2 target);

    private:

        // Assets
        godot::AnimatedSprite2D* animatedSprite_ = nullptr;
        godot::CollisionShape2D* collisionShape_ = nullptr;
        godot::Input* input_ = nullptr;

        // Presets
        static constexpr double cProximityDelta_ = 1.0;

        static constexpr std::string cCollisionShape {"Shape"};
        static constexpr std::string cAnimatedSprite {"AnimatedSprite"};

        static constexpr std::string cAutoRifleAK47 {"AK47"};
        static constexpr std::string cAutoRifleM15 {"M15"};
        static constexpr std::string cPistolLuger {"Luger"};

        // State
        std::vector<exlib::Gun> sling_;

    };
}
