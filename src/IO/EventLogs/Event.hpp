#pragma once
#include <typeindex>

namespace sw::io {
    template<typename EventType>
    struct Event {
    public:
        virtual ~Event() = default;

        [[nodiscard]] std::type_index getTypeIndex() const
        {
            return typeid(EventType);
        }

        EventType* getEventType() {
            return static_cast<EventType*>(this);
        }
    };
}
