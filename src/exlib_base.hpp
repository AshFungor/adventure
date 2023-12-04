// STD
#include <memory>

// Godot
#include <godot_cpp/classes/engine.hpp>

// Poco
#include <Poco/UUID.h>

#pragma once

namespace exlib {

    class ExlibBase {
        Poco::UUID exlib_obj_id {};
        bool exlib_editor {};

    public:
        ExlibBase()
        : exlib_editor{godot::Engine::get_singleton()->is_editor_hint()}
        {}

        ExlibBase(const ExlibBase& other) {
            exlib_obj_id = Poco::UUID{};
            exlib_editor = other.exlib_editor;
        }

        Poco::UUID exlib_get_id() { return exlib_obj_id; }
        bool exlib_editor_hint() { return exlib_editor; }

    };

}
