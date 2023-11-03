#include "Arms/arms.hpp"

void godot::Arms::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(sprite_rotation, Arms, godot::Variant::INT)
}

godot::Arms::Arms() : m_editor {Engine::get_singleton()->is_editor_hint()}
{
    plog::init(plog::Severity::info, EXLIB_LOCAL_BUILD_DIR"/log.txt", 100'000, 3);
    m_animated_sprite = std::make_unique<AnimatedSprite2D>
        (AnimatedSprite2D{});
    m_animated_sprite->set_name(c_animated_sprite.data());
    m_collision_shape = std::make_unique<godot::CollisionShape2D>
        (godot::CollisionShape2D{});
    m_collision_shape->set_name(c_collision_shape.data());
}

void godot::Arms::_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root = get_tree()->get_edited_scene_root();
    if (!has_node(c_animated_sprite.data())) {
        add_child(m_animated_sprite.get());
        m_animated_sprite->set_owner(root);
    } else {
        m_animated_sprite.reset(
            get_node<godot::AnimatedSprite2D>(c_animated_sprite.data()));
    }
    if (!has_node(c_collision_shape.data())) {
        add_child(m_collision_shape.get());
        m_collision_shape->set_owner(root);
    } else {
        m_collision_shape.reset(
            get_node<godot::CollisionShape2D>(c_collision_shape.data()));
    }
    m_input.reset(godot::Input::get_singleton());
}

double godot::Arms::get_rotation_angle(godot::Vector2 base, godot::Vector2 target) {
    double k {0}, arctg {0};
    if (base.x - target.x != 0) {
        // Get coefficient k according to Kramer's rule
        k = (base.y - target.y) / (base.x - target.y);
        arctg = std::atan(k);
    }
    if (base.x > target.x) arctg -= M_PI;
    return arctg;
}

void godot::Arms::_physics_process(const double delta) {

    // Calculate rotation.
    auto&& global_pos_base = get_global_position();
    auto&& global_pos_mouse = get_viewport()->get_mouse_position();
    auto&& rotation_angle = get_rotation_angle(global_pos_base,
                                               global_pos_mouse);
    PLOG_INFO << "rotation_angle: " << rotation_angle;
    if (std::abs(rotation_angle) > M_PI / 2) {
        sprite_rotation = RelativeRot::left;
        m_animated_sprite->set_flip_v(true);
        rotation_angle = std::clamp(std::abs(rotation_angle), M_PI * 3 / 4, M_PI) *
                         -1 * (rotation_angle < 0);
    } else {
        sprite_rotation = RelativeRot::right;
        m_animated_sprite->set_flip_v(false);
        rotation_angle = std::clamp(rotation_angle, -M_PI * 1 / 4, M_PI * 1 / 4);
    }
    PLOG_INFO << "resulting angle: " << rotation_angle;

    rotation_angle = std::fmod(rotation_angle, 2 * M_PI);
    set_rotation(rotation_angle);

    return;
}

godot::Arms::~Arms() {
    m_animated_sprite.release();
    m_collision_shape.release();
    m_input.release();
}
