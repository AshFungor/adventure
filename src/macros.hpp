 // File containing general macros
#include <godot_cpp/core/class_db.hpp>

 // Macro-function overload matcher. Arguments fill _1, _2, ..., _n
 // positions, and the rest is dedicated to macro-function names.
 // When called with k arguments (k <= n) names are pushed k positions
 // behind and then the resulting name is acquired.
#define __EXLIB_MATCH_MACRO_RP(_1, _2, _3, _4, name, ...) name

/* Property registration macro.
 * To use this macro, define EXLIB_PROPERTY in body definition. This macro registers
 * property's getter, setter and actual property.
 */
#define EXLIB_REGISTER_PROPERTY(...)                                                               \
    __EXLIB_MATCH_MACRO_RP(__VA_ARGS__,                                                            \
    __EXLIB_RP_WITH_4,                                                                             \
    __EXLIB_RP_WITH_3)(__VA_ARGS__)

#define __EXLIB_PROPERTY(t_type, name, default_value, setter, getter)                              \
    private: t_type name {default_value};                                                          \
    public:                                                                                        \
        t_type getter () const { return name; }                                                    \
        void setter (t_type value) { name = value; }                                               \
    private:

#define __EXLIB_PROPERTY_ENUM(t_enum_type, name, default_value, setter, getter)                    \
    private: t_enum_type name {default_value};                                                          \
    public:                                                                                        \
    int getter () const { return (int) name; }                                                     \
    void setter (int value) { name = (t_enum_type) value; }                                        \
    private:

#define __EXLIB_RP_WITH_3(name, owner, g_type)                                                     \
    __EXLIB_REGISTER_PROPERTY_3(name, owner, g_type, _set_ ## name, _get_ ## name)

#define __EXLIB_REGISTER_PROPERTY_3(name, owner, g_type, setter, getter)                           \
    godot::ClassDB::bind_method(D_METHOD(#getter),                                                 \
        &owner::getter);                                                                           \
    godot::ClassDB::bind_method(D_METHOD(#setter),                                                 \
        &owner::setter);                                                                           \
    godot::ClassDB::add_property(#owner,                                                           \
        godot::PropertyInfo(g_type, #name),                                                        \
        #setter, #getter);

#define EXLIB_PROPERTY(t_type, name, default_value)                                                \
    __EXLIB_PROPERTY(t_type, name, default_value, _set_ ## name, _get_ ## name)

#define EXLIB_PROPERTY_ENUM(t_enum_type, name, default_value)                                      \
    __EXLIB_PROPERTY_ENUM(t_enum_type, name, default_value, _set_ ## name, _get_ ## name)

#define EXLIB_REGISTER_CLASS(name)                                                                 \
    godot::ClassDB::register_class<godot::name>();

#define EXLIB_EDITOR_SAFEGUARD()                                                                   \
    if (m_editor) {                                                                                \
        set_process(false);                                                                        \
        set_physics_process(false);                                                                \
    }

#define EXLIB_LOCAL_BUILD_DIR                                                                      \
    "/home/fungor/extended-hard-drive/projects/cplusplus-projects/adventure/build"
