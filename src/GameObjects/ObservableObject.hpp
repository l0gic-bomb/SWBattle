#pragma once

#include "../IO/System/EventLog.hpp"
#include <memory>
#include <queue>

namespace sw::game {
    class ObservableObject {
    public:
        void setObserver(const std::shared_ptr<sw::EventLog>& observer) {
            eventLog = observer;
        }

        template<class TEvent>
        void pushEvent(io::Event <TEvent> *event) {
            if (eventLog)
                eventLog->log(event);
        }

        std::shared_ptr<sw::EventLog> getEventLog() {
            return eventLog;
        }

    private:
        // we can generalize it
        std::shared_ptr<sw::EventLog> eventLog;
    };
}
