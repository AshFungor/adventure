#include "Arms/arms.hpp"

void godot::Arms::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(sprite_rotation, Arms, godot::Variant::INT)
}

godot::Arms::Arms() : m_editor {Engine::get_singleton()->is_editor_hint()}
{
    plog::init(plog::Severity::info, EXLIB_BUILD_DIR"/log.txt", 100'000, 3);
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimatedSprite2D, animated_sprite)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::CollisionShape2D, collision_shape)
}

void godot::Arms::_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root = get_tree()->get_edited_scene_root();
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::AnimatedSprite2D, animated_sprite, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::CollisionShape2D, collision_shape, root)
    m_input.reset(godot::Input::get_singleton());
}

double godot::Arms::get_rotation_angle(godot::Vector2 base, godot::Vector2 target) {
    double k {0}, arctg {0};
    if (base.x - target.x != 0) {
        // Get coefficient k according to Kramer's rule
        k = (base.y - target.y) / (base.x - target.x);
        arctg = std::atan(k);
    }
    return arctg;
}

void godot::Arms::_physics_process(const double delta) {

    // Calculate rotation.
    auto&& global_pos_base = get_global_position();
    auto&& global_pos_mouse = get_viewport()->get_mouse_position();
    auto&& rotation_angle = get_rotation_angle(global_pos_base,
                                               global_pos_mouse);
    if (global_pos_base.x > global_pos_mouse.x) {
        sprite_rotation = RelativeRot::left;
        m_animated_sprite->set_flip_h(true);
        rotation_angle = std::clamp(rotation_angle, -M_PI * 1 / 4, M_PI * 1 / 4);
    } else {
        sprite_rotation = RelativeRot::right;
        m_animated_sprite->set_flip_h(false);
        rotation_angle = std::clamp(rotation_angle, -M_PI * 1 / 4, M_PI * 1 / 4);
    }

    rotation_angle = std::fmod(rotation_angle, 2 * M_PI);
    set_rotation(rotation_angle);

    PLOG_INFO << get_rotation();

    return;
}

godot::Arms::~Arms() {
    m_animated_sprite.release();
    m_collision_shape.release();
    m_input.release();
}
