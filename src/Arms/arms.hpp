// Local
#include "macros.hpp"

// STD headers.
#include <memory>
#include <algorithm>

// Godot headers.
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

namespace godot {

    class Arms : public Node2D {
        GDCLASS(Arms, Node2D)

    protected:
        static void _bind_methods();

    public:

    };
}
