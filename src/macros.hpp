 // File containing general macros
#include <godot_cpp/core/class_db.hpp>

#define __LIB_PROPERTY(t_type, name, default_value, setter, getter) \
    private: t_type name {default_value};                           \
    public:                                                         \
        t_type getter () const { return name; }                \
        void setter (t_type value) { name = value; }           \
    private:

#define __LIB_REGISTER_PROPERTY(name, owner, setter, getter)    \
    godot::ClassDB::bind_method(D_METHOD(#getter),              \
        &owner::getter);                                        \
    godot::ClassDB::bind_method(D_METHOD(#setter),              \
        &owner::setter);                                        \
    godot::ClassDB::add_property(#owner,                        \
        godot::PropertyInfo(godot::Variant::FLOAT, #name),      \
        #setter, #getter);

#define LIB_PROPERTY(t_type, name, default_value)  \
    __LIB_PROPERTY(t_type, name, default_value, set ## name, get ## name)

#define LIB_REGISTER_PROPERTY(name, owner)                          \
    __LIB_REGISTER_PROPERTY(name, owner, set ## name, get ## name)
