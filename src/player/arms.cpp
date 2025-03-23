#include <algorithm>

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <src/common/nodes.hpp>
#include <src/player/arms.hpp>

static const char* const ARMS_SPRITE = "AnimatedSprite";
static const char* const ARMS_COLLISION_SHAPE = "CollisionShape";

using namespace tomato;

void Arms::_bind_methods() {
    godot::PropertyInfo spriteRotationProperty{godot::Variant::INT, "sprite_rotation"};
    tomato::registerProperty("Arms", "set_sprite_rotation", "sprite_rotation", spriteRotationProperty, &Arms::setSpriteRotation,
                             &Arms::spriteRotation);
}

void Arms::_ready() {
    tomato::disableEditorProcessing(this);
    collisionShape_ = tomato::loadNode<godot::CollisionShape2D>(this, ARMS_COLLISION_SHAPE);
    animatedSprite_ = tomato::loadNode<godot::AnimatedSprite2D>(this, ARMS_SPRITE);

    input_ = godot::Input::get_singleton();
}

int Arms::spriteRotation() const {
    return static_cast<int>(spriteRotation_);
}

void Arms::setSpriteRotation(int value) {
    spriteRotation_ = tomato::clampEnumValue(value, RelativeRotation::MIN_VALUE, RelativeRotation::MAX_VALUE);
}

double Arms::rotationAngle(godot::Vector2 base, godot::Vector2 target) {
    double k = 0;
    double arctg = 0;
    if (base.x - target.x != 0) {
        // Get coefficient k according to Kramer's rule
        k = (base.y - target.y) / (base.x - target.x);
        arctg = std::atan(k);
    }
    return arctg;
}

void Arms::_physics_process(const double delta) {
    // Calculate rotation
    godot::Vector2 currentPos = get_global_position();
    godot::Vector2 mousePos = get_viewport()->get_mouse_position();
    auto rotation_angle = rotationAngle(currentPos, mousePos);

    if (currentPos.x > mousePos.x) {
        spriteRotation_ = RelativeRotation::LEFT;
        animatedSprite_->set_flip_h(true);
    } else {
        spriteRotation_ = RelativeRotation::RIGHT;
        animatedSprite_->set_flip_h(false);
    }

    rotation_angle = std::clamp(rotation_angle, -M_PI * 1 / 4, M_PI * 1 / 4);
    rotation_angle = std::fmod(rotation_angle, 2 * M_PI);
    set_rotation(rotation_angle);
}
