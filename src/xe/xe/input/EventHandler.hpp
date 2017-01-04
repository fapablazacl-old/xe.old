
#pragma once 

#ifndef __xe_input_eventhandler__
#define __xe_input_eventhandler__

namespace xe {
    template<typename EventData>
    class EventHandler {
    public:
        virtual bool handleEvent(const EventData &) = 0;
    };
}

#endif 
