#include <cassert>
#include <godot_cpp/classes/engine.hpp>
#include <src/common/initializer.hpp>

using namespace tomato;

void tomato::disableEditorProcessing(godot::Node* target) {
    assert(target);

    if (godot::Engine::get_singleton()->is_editor_hint()) {
        target->set_process(false);
        target->set_physics_process(false);
    }
}