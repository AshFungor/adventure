#pragma once

// STD
#include <cmath>

// Godot
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/godot.hpp>

namespace tomato {

    class Arms : public godot::Area2D {
        GDCLASS(Arms, godot::Area2D)

    public:
        enum class RelativeRotation : int { LEFT, ALIGNED, RIGHT, MAX_VALUE = RIGHT, MIN_VALUE = LEFT };

        /* properties */
        int spriteRotation() const;
        void setSpriteRotation(int value);

        /* godot node */
        void _ready() override;
        void _physics_process(const double delta) override;

    protected:
        static void _bind_methods();

    private:
        double rotationAngle(godot::Vector2 base, godot::Vector2 target);

    private:
        /* properties */
        RelativeRotation spriteRotation_ = RelativeRotation::RIGHT;

        /* node contents */
        godot::AnimatedSprite2D* animatedSprite_ = nullptr;
        godot::CollisionShape2D* collisionShape_ = nullptr;

        /* references to global engine state */
        godot::Input* input_ = nullptr;
    };

}  // namespace tomato
