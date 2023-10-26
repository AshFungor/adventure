#include "example.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Example::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_amplitude"), &Example::set_amplitude);
    ClassDB::bind_method(D_METHOD("get_amplitude"), &Example::get_amplitude);
    ClassDB::add_property("Example", PropertyInfo(Variant::FLOAT, "Amplitude"),
                          "set_amplitude",
                          "get_amplitude");
}

Example::Example() {
    // Initialize any variables here.
}

Example::~Example() {
    // Add your cleanup here.
}

void Example::set_amplitude(double value) { amplitude = value; }
double Example::get_amplitude() const { return amplitude; }

void Example::_process(double delta) {
    time_passed += delta;

    Vector2 new_position = Vector2(amplitude + (amplitude * sin(time_passed * 2.0)),
                                   amplitude + (amplitude * cos(time_passed * 1.5)));

    set_position(new_position);
}
