#include <algorithm>
#include <cstddef>

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <src/common/def.hpp>
#include <src/common/nodes.hpp>
#include <src/player/arms.hpp>
#include <src/player/player.hpp>

using namespace tomato;

static const char* const PLAYER_ANIMATED_SPRITE = "AnimatedSprite";
static const char* const PLAYER_COLLISION_SHAPE = "CollisionShape";
static const char* const PLAYER_ARMS = "Arms";

constexpr std::size_t PLAYER_ANIM_WALKING_RIGHT = 0;
constexpr std::size_t PLAYER_ANIM_WALKING_LEFT = 1;
constexpr std::size_t PLAYER_ANIM_IDLE = 2;
constexpr std::size_t PLAYER_ANIM_WALKING_RIGHT_BACKWARDS = 3;
constexpr std::size_t PLAYER_ANIM_WALKING_LEFT_BACKWARDS = 4;

static const std::array<const char*, 5> PLAYER_ANIMATIONS = {"walking_right", "walking_left", "idle", "walking_right_backwards",
                                                             "walking_left_backwards"};

void Player::_bind_methods() {
    // props info
    godot::PropertyInfo speedProperty{godot::Variant::FLOAT, "speed"};
    tomato::registerProperty("Player", "set_speed", "speed", speedProperty, &Player::setSpeed, &Player::speed);
}

real_t Player::speed() const {
    return speed_;
}

void Player::setSpeed(real_t value) {
    speed_ = std::max(value, 0.0f);
}

void Player::_ready() {
    tomato::disableEditorProcessing(this);
    animatedSprite_ = tomato::loadNode<godot::AnimatedSprite2D>(this, PLAYER_ANIMATED_SPRITE);
    collisionShape_ = tomato::loadNode<godot::CollisionShape2D>(this, PLAYER_COLLISION_SHAPE);
    arms_ = tomato::loadNode<tomato::Arms>(this, PLAYER_ARMS);

    input_ = godot::Input::get_singleton();
    screenSize_ = get_viewport_rect().size;
}

void Player::_physics_process(const double p_delta) {
    godot::Vector2 velocity = {0, 0};

    velocity.x = input_->get_action_strength("move_right") - input_->get_action_strength("move_left");
    velocity.y = input_->get_action_strength("move_down") - input_->get_action_strength("move_up");

    if (velocity.length() > 0) {
        // We need to normalize velocity, so that diagonal movement
        // will be equal to movement on an axis.
        velocity = velocity.normalized() * speed_;
        if (velocity.x > 0) {
            if (arms_->spriteRotation() == static_cast<int>(tomato::Arms::RelativeRotation::LEFT)) {
                animatedSprite_->play(PLAYER_ANIMATIONS[PLAYER_ANIM_WALKING_RIGHT_BACKWARDS]);
            } else {
                animatedSprite_->play(PLAYER_ANIMATIONS[PLAYER_ANIM_WALKING_RIGHT]);
            }
        } else {
            if (arms_->spriteRotation() == static_cast<int>(tomato::Arms::RelativeRotation::RIGHT)) {
                animatedSprite_->play(PLAYER_ANIMATIONS[PLAYER_ANIM_WALKING_LEFT_BACKWARDS]);
            } else {
                animatedSprite_->play(PLAYER_ANIMATIONS[PLAYER_ANIM_WALKING_LEFT]);
            }
        }
    } else {
        animatedSprite_->play(PLAYER_ANIMATIONS[PLAYER_ANIM_IDLE]);
    }

    auto position = get_position();
    position += velocity * static_cast<real_t>(p_delta);
    position.x = std::clamp(position.x, 0.0f, screenSize_.x);
    position.y = std::clamp(position.y, 0.0f, screenSize_.y);
    set_position(position);
}