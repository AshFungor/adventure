#include "player.hpp"

void godot::Player::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(speed, Player, godot::Variant::FLOAT)
}

void godot::Player::_enter_tree() {
    auto&& root_scene = get_tree();
    if (!has_node(c_animated_sprite.data())) {
        m_animated_sprite = std::make_unique<godot::AnimatedSprite2D>(AnimatedSprite2D{});
        // This works for some reason, Editor allows to change sprites.
        SpriteFrames frames {};
        m_animated_sprite->set_sprite_frames(&frames);
        m_animated_sprite->set_name(c_animated_sprite.data());
        add_child(m_animated_sprite.get());
        m_animated_sprite->set_owner(root_scene->get_edited_scene_root());
    } else {
        if (m_animated_sprite) goto end_node_init_1;
        m_animated_sprite.reset(get_node<godot::AnimatedSprite2D>(c_animated_sprite.data()));
    }
    end_node_init_1:
    if (!has_node(c_collision_shape_name.data())) {
        m_collision_shape = std::make_unique<godot::CollisionShape2D>(CollisionShape2D{});
        m_collision_shape->set_name(c_collision_shape_name.data());
        add_child(m_collision_shape.get());
        m_collision_shape->set_owner(root_scene->get_edited_scene_root());
    } else {
        if (!m_collision_shape) goto end_node_init_2;
        m_collision_shape.reset(get_node<godot::CollisionShape2D>(c_collision_shape_name.data()));
    }
    end_node_init_2:
    return;
}

void godot::Player::_ready() {
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

    m_animated_sprite->set_flip_h(velocity.x < 0);

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
