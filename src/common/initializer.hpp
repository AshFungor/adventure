#pragma once

#include <cassert>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/string.hpp>
#include <type_traits>

namespace tomato {

    template <typename T>
    T* loadNode(godot::Node* parent, const godot::NodePath& path);

    void disableEditorProcessing(godot::Node* target);

}  // namespace tomato

template <typename T>
T* tomato::loadNode(godot::Node* parent, const godot::NodePath& path) {
    static_assert(std::is_default_constructible<T>());
    static_assert(std::is_base_of<godot::Node, T>());
    assert(parent);

    if (parent->has_node(path)) {
        return parent->get_node<T>(path);
    }

    T* instance = new T();
    parent->add_child(instance);
    // set_owner is used to preserve this node later
    // https://docs.godotengine.org/en/stable/classes/class_node.html#class-node-method-add-child
    godot::Node* sceneRoot = parent->get_tree()->get_edited_scene_root();
    instance->set_owner(sceneRoot);
    instance->set_name(path.get_name(0));
    return instance;
}