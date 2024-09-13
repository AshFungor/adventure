 // File containing general macros
#include <godot_cpp/core/class_db.hpp>

#pragma once

#define EXLIB_ABORT_IF(condition) \
    if ((condition)) std::abort()

#define EXLIB_EXECUTION_SAFEGUARD() \
    if (!baseShouldExecute()) return;
