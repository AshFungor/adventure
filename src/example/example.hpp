#include <godot_cpp/classes/sprite2d.hpp>

#pragma once

namespace godot {

class Example : public Sprite2D {
    GDCLASS(Example, Sprite2D)

private:
    double time_passed {0};
    double amplitude {10};

protected:
    static void _bind_methods();

public:
    Example();
    ~Example();

    void set_amplitude(double value);
    double get_amplitude() const;

    void _process(double delta) override;
};

}
