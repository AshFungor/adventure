#include "Player/player.hpp"
#include "Arms/arms.hpp"
#include "macros.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input_map.hpp>

void initialize_gdextension_types(godot::ModuleInitializationLevel p_level)
{
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
    }

    EXLIB_REGISTER_CLASS(Player)
    EXLIB_REGISTER_CLASS(Arms)

    // All initialization goes here.
}

void uninitialize_gdextension_types(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

// Initialization
extern "C" GDExtensionBool GDE_EXPORT extension_lib_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization)
{
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
    init_obj.register_initializer(initialize_gdextension_types);
    init_obj.register_terminator(uninitialize_gdextension_types);
    init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
