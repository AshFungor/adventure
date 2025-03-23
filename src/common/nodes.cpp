#include <cassert>
#include <godot_cpp/classes/engine.hpp>
#include <src/common/nodes.hpp>

using namespace tomato;

void tomato::disableEditorProcessing(godot::Node* target) {
    assert(target);

    const godot::Engine* engine = godot::Engine::get_singleton();
    if (engine->is_editor_hint()) {
        target->set_physics_process(false);
        target->set_process(false);
    }
}