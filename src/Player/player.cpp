#include "player.hpp"

void godot::Player::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(speed, Player, godot::Variant::FLOAT)
}

godot::Player::Player() : m_editor {Engine::get_singleton()->is_editor_hint()}
{
    m_animated_sprite = std::make_unique<godot::AnimatedSprite2D>(AnimatedSprite2D{});
    m_animated_sprite->set_name(c_animated_sprite.data());
    m_collision_shape = std::make_unique<godot::CollisionShape2D>(CollisionShape2D{});
    m_collision_shape->set_name(c_collision_shape.data());
}

void godot::Player::_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root_scene = get_tree();
    // Adjust pointers to child nodes.
    if (has_node(c_animated_sprite.data())) {
        m_animated_sprite.reset(
            get_node<godot::AnimatedSprite2D>(c_animated_sprite.data()));
    } else {
        m_animated_sprite->set_owner(root_scene->get_edited_scene_root());
        add_child(m_animated_sprite.get());
    }
    if (has_node(c_collision_shape.data())) {
        m_collision_shape.reset(
            get_node<godot::CollisionShape2D>(c_animated_sprite.data()));
    } else {
        m_collision_shape->set_owner(root_scene->get_edited_scene_root());
        add_child(m_collision_shape.get());
    }
    m_input = godot::Input::get_singleton();
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
            m_animated_sprite->play(c_walking_right_animation.data());
        } else {
            m_animated_sprite->play(c_walking_left_animation.data());
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
}

void godot::Player::start(const godot::Vector2 p_position) {}
void godot::Player::_on_body_entered(std::unique_ptr<godot::Node2D> _body) {}
