#include "player.hpp"

void godot::Player::_bind_methods() {
    LIB_REGISTER_PROPERTY(speed, Player);
}

void godot::Player::_ready() {
    auto&& input_map = godot::InputMap::get_singleton();
    input_map->load_from_project_settings();
    m_animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");
    m_collision_shape = get_node<godot::CollisionShape2D>("CollisionShape2D");
    m_input = godot::Input::get_singleton();
    m_screen_size = get_viewport_rect().size;
}

void godot::Player::_process(const double p_delta) {
    godot::Vector2 velocity = {0, 0};

    velocity.x = m_input->get_action_strength("move_right")
                 - m_input->get_action_strength("move_left");
    velocity.y = m_input->get_action_strength("move_down")
                 - m_input->get_action_strength("move_up");

    if (velocity.length() > 0) {
        // We need to normalize velocity, so that diagonal movement
        // will be equal to movement on an axis.
        velocity = velocity.normalized() * speed;
        m_animated_sprite->play();
    } else {
        m_animated_sprite->stop();
    }

    auto position = get_position();
    position += velocity * static_cast<real_t>(p_delta);
    position.x = std::clamp(position.x, static_cast<real_t>(0.0), m_screen_size.x);
    position.y = std::clamp(position.y, static_cast<real_t>(0.0), m_screen_size.y);
    set_position(position);
}

void godot::Player::start(const godot::Vector2 p_position) {}
void godot::Player::_on_body_entered(std::unique_ptr<godot::Node2D> _body) {}
