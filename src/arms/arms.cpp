#include <algorithm>
#include <godot_cpp/variant/vector2.hpp>
#include <src/macros.hpp>
#include <src/arms/arms.hpp>

using namespace exlib;

void Arms::_bind_methods() {
    // EXLIB_REGISTER_PROPERTY(sprite_rotation, Arms, godot::Variant::INT)
}

Arms::Arms() {
    // EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimatedSprite2D, animated_sprite)
    // EXLIB_INITIALIZE_DEFAULT_NODE(godot::CollisionShape2D, collision_shape)
}

void Arms::_ready() {
    EXLIB_EXECUTION_SAFEGUARD();
    auto&& root = get_tree()->get_edited_scene_root();
    
    input_ = godot::Input::get_singleton();
}

double Arms::get_rotation_angle(godot::Vector2 base, godot::Vector2 target) {
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

    // Calculate rotation.
    godot::Vector2 globalCurrentPosition = get_global_position();
    godot::Vector2 globalMousePosition = get_viewport()->get_mouse_position();
    auto rotation_angle = get_rotation_angle(globalCurrentPosition,
                                               globalMousePosition);
    if (globalCurrentPosition.x > globalMousePosition.x) {
        // sprite_rotation = RelativeRot::left;
        animatedSprite_->set_flip_h(true);
    } else {
        // sprite_rotation = RelativeRot::right;
        animatedSprite_->set_flip_h(false);
    }

    rotation_angle = std::clamp(rotation_angle, -M_PI * 1 / 4, M_PI * 1 / 4);
    rotation_angle = std::fmod(rotation_angle, 2 * M_PI);
    set_rotation(rotation_angle);

    // PLOG_INFO << get_rotation();

    return;
}
