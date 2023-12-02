#include "weapon.hpp"

using namespace godot::weapons;

void AK47::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(damage, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(recoil, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(firerate, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(precision, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(shot_speed, AK47, godot::Variant::FLOAT)
}

void AK47::_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root = get_tree()->get_edited_scene_root();
    // Adjust pointers to child nodes.
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::AnimatedSprite2D, weapon_sprite, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::CollisionShape2D, weapon_shape, root)
}

void AK47::_physics_process(const double p_delta) {}

void AK47::m_reload() {}
void AK47::m_shoot() {}
void AK47::m_get_gun() {}
void AK47::m_remove_gun() {}

AK47::AK47() {
    m_editor = Engine::get_singleton()->is_editor_hint();
    m_id = Poco::UUID{};
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimatedSprite2D, weapon_sprite)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::CollisionShape2D, weapon_shape)
}
AK47::~AK47() {
    m_weapon_shape.release();
    m_weapon_sprite.release();
}
