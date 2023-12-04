#include "weapon.hpp"

using namespace godot::weapons;

Weapon::Weapon() {
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimationPlayer, weapon_animation)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::AnimatedSprite2D, weapon_sprite)
    EXLIB_INITIALIZE_DEFAULT_NODE(godot::CollisionShape2D, weapon_shape)
}

void Weapon::m_ready() {
    EXLIB_EDITOR_SAFEGUARD()
    auto&& root = get_tree()->get_edited_scene_root();
    // Adjust pointers to child nodes.
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::AnimatedSprite2D, weapon_sprite, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::CollisionShape2D, weapon_shape, root)
    EXLIB_INITILIZE_NODE_FROM_SCENE(godot::AnimationPlayer, weapon_animation, root)
}

Weapon::~Weapon() {
    m_weapon_animation.release();
    m_weapon_shape.release();
    m_weapon_sprite.release();
}
