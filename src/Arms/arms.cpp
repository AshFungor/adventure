 #include "Arms/arms.hpp"

void godot::Arms::_bind_methods() {}

void godot::Arms::_enter_tree() {
    auto&& root = get_tree()->get_edited_scene_root();
    if (!has_node(c_animated_sprite.data())) {
        m_animated_sprite = std::make_unique<AnimatedSprite2D>(AnimatedSprite2D{});
        m_animated_sprite->set_name(c_animated_sprite.data());
        add_child(m_animated_sprite.get());
        m_animated_sprite->set_owner(root);
    } else {
        if (m_animated_sprite) goto end_init_1;
        m_animated_sprite.reset(get_node<godot::AnimatedSprite2D>(c_animated_sprite.data()));
    }
    end_init_1:
    if (!m_animated_sprite->get_sprite_frames().ptr()) {
        m_sprite_frames = std::make_unique<godot::SpriteFrames>(godot::SpriteFrames{});
        m_animated_sprite->set_sprite_frames(m_sprite_frames.get());
    } else {
        if (!m_sprite_frames)
        m_sprite_frames.reset(m_animated_sprite->get_sprite_frames().ptr());
    }
    if (!has_node(c_shape.data())) {
        m_shape = std::make_unique<godot::CollisionShape2D>(godot::CollisionShape2D{});
        m_shape->set_name(c_shape.data());
        add_child(m_shape.get());
        m_shape->set_owner(root);
    } else {
        if (m_shape) goto end_init_2;
        m_shape.reset(get_node<godot::CollisionShape2D>(c_shape.data()));
    }
    end_init_2:
    auto&& shape = m_shape->get_shape();
    if (!shape.ptr() || dynamic_cast<godot::RectangleShape2D*>(shape.ptr())) {
        m_rect_shape = std::make_unique<godot::RectangleShape2D>(godot::RectangleShape2D{});
        m_shape->set_shape(m_rect_shape.get());
    } else {
        if (!m_rect_shape)
        m_rect_shape.reset(dynamic_cast<godot::RectangleShape2D*>(shape.ptr()));
    }
    return;
}

void godot::Arms::_ready() {
    m_input.reset(godot::Input::get_singleton());
    auto&& size = (m_rect_shape->get_size());
    m_current_null_point = m_shape->get_global_position() + size / 2;
}

void godot::Arms::_physics_process(const double delta) {
    auto&& mouse_pos = get_viewport()->get_mouse_position();
    look_at(mouse_pos);

    return;
}

godot::Arms::~Arms() {
    m_animated_sprite.release();
    m_shape.release();
    m_input.release();
}
