 // File containing general macros
#include <godot_cpp/core/class_db.hpp>

#define __EXLIB_MATCH_MACRO_RP(_1, _2, _3, _4, name, ...) name

#define EXLIB_REGISTER_PROPERTY(...)                                                               \
    __EXLIB_MATCH_MACRO_RP(__VA_ARGS__,                                                            \
    __EXLIB_RP_WITH_4,                                                                               \
    __EXLIB_RP_WITH_3)(__VA_ARGS__)

#define __EXLIB_PROPERTY(t_type, name, default_value, setter, getter)                              \
    private: t_type name {default_value};                                                          \
    public:                                                                                        \
        t_type getter () const { return name; }                                                    \
        void setter (t_type value) { name = value; }                                               \
    private:

#define __EXLIB_RP_WITH_3(name, owner, g_type)                                                     \
    __EXLIB_REGISTER_PROPERTY_3(name, owner, g_type, set ## name, get ## name)

#define __EXLIB_REGISTER_PROPERTY_3(name, owner, g_type, setter, getter)                           \
    godot::ClassDB::bind_method(D_METHOD(#getter),                                                 \
        &owner::getter);                                                                           \
    godot::ClassDB::bind_method(D_METHOD(#setter),                                                 \
        &owner::setter);                                                                           \
    godot::ClassDB::add_property(#owner,                                                           \
        godot::PropertyInfo(g_type, #name),                                                        \
        #setter, #getter);

#define EXLIB_PROPERTY(t_type, name, default_value)                                                \
    __EXLIB_PROPERTY(t_type, name, default_value, set ## name, get ## name)
