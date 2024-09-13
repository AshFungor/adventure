// STD
#include <cstdint>
#include <memory>

// Godot
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/engine.hpp>

// local
#include <src/base.hpp>
#include <src/macros.hpp>

using namespace exlib;


IdRegistry::IdRegistry(Private access) noexcept
    : head_(PTRDIFF_MIN)
{}

std::shared_ptr<IdRegistry>& IdRegistry::instance() noexcept {
    return instance_;
}

IdRegistry::IdType IdRegistry::acquireId() noexcept {
    if (head_ == PTRDIFF_MAX) {
        EXLIB_ABORT_IF(given_.size() == 1ll << (PTRDIFF_WIDTH - 1));

        // else find closest free head
        head_ = PTRDIFF_MIN;
    }

    while (given_.find(head_) != given_.end()) {
        ++head_;
    }

    given_.insert(head_);
    return head_++;
}

void IdRegistry::returnId(IdType id) noexcept {
    given_.erase(id);
}