#include "player.hpp"

void godot::Player::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(speed, Player, godot::Variant::FLOAT)
}

godot::Player::Player() : m_editor {Engine::get_singleton()->is_editor_hint()}
{
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimatedSprite2D, animated_sprite)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::CollisionShape2D, collision_shape)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::Arms, arms)
}

void godot::Player::_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root = get_tree()->get_edited_scene_root();
    // Adjust pointers to child nodes.
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::AnimatedSprite2D, animated_sprite, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::CollisionShape2D, collision_shape, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::Arms, arms, root)
    EXLIB_INLINE_EDITOR_SAFEGUARD()
    m_input.reset(godot::Input::get_singleton());
    m_screen_size = get_viewport_rect().size;
}

void godot::Player::_physics_process(const double p_delta) {

    godot::Vector2 velocity = {0, 0};

    velocity.x = m_input->get_action_strength("move_right")
                 - m_input->get_action_strength("move_left");
    velocity.y = m_input->get_action_strength("move_down")
                 - m_input->get_action_strength("move_up");

    if (velocity.length() > 0) {
        // We need to normalize velocity, so that diagonal movement
        // will be equal to movement on an axis.
        velocity = velocity.normalized() * speed;
        if (velocity.x > 0) {
            if (m_arms->_get_sprite_rotation() == (int) godot::RelativeRot::left) {
                m_animated_sprite->play(c_walking_right_backwards_animation.data());
            } else {
                m_animated_sprite->play(c_walking_right_animation.data());
            }
        } else {
            if (m_arms->_get_sprite_rotation() == (int) godot::RelativeRot::right) {
                m_animated_sprite->play(c_walking_left_backwards_animation.data());
            } else {
                m_animated_sprite->play(c_walking_left_animation.data());
            }
        }
    } else {
        m_animated_sprite->play(c_idle_animation.data());
    }

    auto position = get_position();
    position += velocity * static_cast<real_t>(p_delta);
    position.x = std::clamp(position.x, static_cast<real_t>(0.0), m_screen_size.x);
    position.y = std::clamp(position.y, static_cast<real_t>(0.0), m_screen_size.y);
    set_position(position);
}

godot::Player::~Player() {
    m_collision_shape.release();
    m_animated_sprite.release();
    m_arms.release();
    m_input.release();
}

void godot::Player::start(const godot::Vector2 p_position) {}
void godot::Player::_on_body_entered(std::unique_ptr<godot::Node2D> _body) {}
