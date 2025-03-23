#include <algorithm>

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <src/common/initializer.hpp>
#include <src/player/arms.hpp>

static const char* const ARMS_SPRITE = "sprite";
static const char* const ARMS_COLLISION_SHAPE = "collision-shape";

static constexpr std::string cAutoRifleAK47{"AK47"};
static constexpr std::string cAutoRifleM15{"M15"};
static constexpr std::string cPistolLuger{"Luger"};

using namespace tomato;

void Arms::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_sprite_rotation"),
                                &Arms::setSpriteRotation);
    godot::ClassDB::bind_method(godot::D_METHOD("sprite_rotation"),
                                &Arms::spriteRotation);
    godot::ClassDB::add_property(
        "Arms", godot::PropertyInfo(godot::Variant::INT, "sprite_rotation"),
        "set_sprite_rotation", "sprite_rotation");
}

void Arms::_ready() {
    tomato::disableEditorProcessing(this);
    collisionShape_ =
        tomato::loadNode<godot::CollisionShape2D>(this, ARMS_COLLISION_SHAPE);
    animatedSprite_ =
        tomato::loadNode<godot::AnimatedSprite2D>(this, ARMS_SPRITE);

    input_ = godot::Input::get_singleton();
}

int Arms::spriteRotation() const { return static_cast<int>(spriteRotation_); }

void Arms::setSpriteRotation(int value) {
    spriteRotation_ = static_cast<RelativeRotation>(value);
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
