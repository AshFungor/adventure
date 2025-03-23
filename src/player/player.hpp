// Local
#include <src/player/arms.hpp>

// Godot
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>

#pragma once

namespace tomato {

    class Player : public godot::Area2D {
        GDCLASS(Player, godot::Area2D)

    public:
        /* properties */
        real_t speed() const;
        void setSpeed(real_t value);

        /* godot node */
        void _ready() override;
        void _physics_process(const double p_delta) override;

    protected:
        // Godot API to bind class members in game Editor.
        static void _bind_methods();

    private:
        /* properties */
        real_t speed_ = 400.0f;

        /* references to global engine state */
        godot::Input* input_ = nullptr;
        godot::Vector2 screenSize_;

        /* node contents */
        godot::AnimatedSprite2D* animatedSprite_ = nullptr;
        godot::CollisionShape2D* collisionShape_ = nullptr;
        tomato::Arms* arms_ = nullptr;
    };

}  // namespace tomato
