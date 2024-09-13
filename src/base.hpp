// STD
#include <godot_cpp/classes/object.hpp>
#include <set>
#include <random>
#include <memory>
#include <cstddef>

// Godot
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/engine.hpp>

#pragma once

namespace exlib {

    // Provides program-wide, runtime-unique identifiers that
    // can be used to distinguish objects.
    class IdRegistry 
        : std::enable_shared_from_this<IdRegistry> {
    private: struct Private { };
    public:

        using IdType = std::ptrdiff_t;

        IdRegistry(Private access) noexcept;
        static std::shared_ptr<IdRegistry>& instance() noexcept;

        IdType acquireId() noexcept;
        void returnId(IdType id) noexcept;

    private:
        // singleton
        static std::shared_ptr<IdRegistry> instance_;
        std::set<IdType> given_;

        // for id generation
        IdType head_;

    };

    // Provides base class for exlib objects
    template<
        bool DoesEditorProcessing,
        bool DoesGameProcessing
    >
    class Base {
    public:

        Base();
        Base(const Base&) = default;
        Base(Base&&) = default;

        ~Base();

    protected:
        bool baseShouldExecute() const noexcept;

    protected:
        // check for editor execution
        const bool baseEditorHint_;
        // runtime-unique id
        const IdRegistry::IdType baseId_;

    };

}


// Definitions
template<
    bool DoesEditorProcessing,
    bool DoesGameProcessing
>
bool exlib::Base<DoesEditorProcessing, DoesGameProcessing>::baseShouldExecute() const noexcept {
    if (baseEditorHint_) {
        return DoesEditorProcessing;
    }
    return DoesGameProcessing;
}

template<
    bool DoesEditorProcessing,
    bool DoesGameProcessing
>
exlib::Base<DoesEditorProcessing, DoesGameProcessing>::Base() 
    : baseEditorHint_(godot::Engine::get_singleton()->is_editor_hint())
    , baseId_(exlib::IdRegistry::instance()->acquireId())
{}

template<
    bool DoesEditorProcessing,
    bool DoesGameProcessing
>
exlib::Base<DoesEditorProcessing, DoesGameProcessing>::~Base() {
    exlib::IdRegistry::instance()->returnId(baseId_);
}