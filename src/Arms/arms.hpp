// Local
#include "macros.hpp"

// STD headers.
#include <memory>
#include <vector>
#include <cmath>

// Godot headers.
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/viewport.hpp>

namespace godot {

    class Arms : public Area2D {
        GDCLASS(Arms, Area2D)

        std::unique_ptr<godot::AnimatedSprite2D> m_animated_sprite {};
        std::unique_ptr<godot::CollisionShape2D> m_shape {};
        std::unique_ptr<godot::SpriteFrames> m_sprite_frames {};
        std::unique_ptr<godot::RectangleShape2D> m_rect_shape {};
        std::unique_ptr<godot::Input> m_input {};
        double m_rotation_angle {0};
        godot::Vector2 m_current_null_point {};

        const double c_proximity_delta = 1.0;

        const std::string c_shape {"Shape"};
        const std::string c_animated_sprite {"AnimatedSprite"};

        // Weapons
        const std::string c_auto_rifle_ak_47 {"AK47"};
        const std::string c_auto_rifle_m15 {"M15"};
        const std::string c_pistol_luger {"Luger"};

        std::vector<std::string> m_sling {};

    protected:
        static void _bind_methods();

    public:

        void _enter_tree() override;
        void _ready() override;
        void _physics_process(const double delta) override;
        ~Arms();
    };
}
