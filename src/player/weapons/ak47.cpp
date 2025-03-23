#include "weapon.hpp"

using namespace godot::weapons;

void AK47::_bind_methods() {
    EXLIB_REGISTER_PROPERTY(damage, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(recoil, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(firerate, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(precision, AK47, godot::Variant::FLOAT)
    EXLIB_REGISTER_PROPERTY(shot_speed, AK47, godot::Variant::FLOAT)
}

void AK47::_ready() {
    m_ready();
}

void AK47::_physics_process(const double p_delta) {

}

void AK47::m_reload() {}
void AK47::m_shoot() {}
void AK47::m_get_gun() {}
void AK47::m_remove_gun() {}
