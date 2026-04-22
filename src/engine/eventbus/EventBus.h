//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_EVENTBUS_H
#define CMATERIAL_EVENTBUS_H


#include <vector>
#include <unordered_map>
#include <mutex>

#include "IListener.h"


namespace cmaterial::event {
    class IListener;
    class IHandler;
    class IEvent;

    class EventBus {
    public:
        ~EventBus();

        static void addListener(IListener* listener);
        static void postEvent(IEvent* event);
        static bool dispatch();

        static void removeListener(IListener* listener);
        static void shutdown();

    private:
        static std::vector<IListener*> registeredListeners;
        static std::unordered_map<const void*, std::vector<IHandler*>> subscriberMap;

        static std::mutex registerMutex;

        static std::vector<IEvent*> eventQueue ;
        static std::mutex queueMutex;
    };
}




#endif //CMATERIAL_EVENTBUS_H
