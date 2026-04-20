//
// Created by Earth_Studio on 2026/4/16.
//

#include "EventBus.h"
#include <algorithm>
#include "GLFW/glfw3.h"
#include "IEvent.h"
#include "IListener.h"

namespace cmaterial::event {
    std::vector<IListener*> EventBus::registeredListeners;
    std::unordered_map<const void*, std::vector<IHandler*>> EventBus::subscriberMap;

    std::vector<IEvent*> EventBus::eventQueue ;
    std::mutex EventBus::queueMutex;
    std::mutex EventBus::registerMutex;

    void EventBus::addListener(IListener* listener) {
        if (!listener) return;

        std::lock_guard<std::mutex> lock(registerMutex);

        registeredListeners.push_back(listener);

        for (auto* handler : listener->getHandlers()) {
            auto& vec = subscriberMap[handler->getEventType()];
            vec.push_back(handler);

            std::sort(vec.begin(), vec.end(),[](IHandler* a, IHandler* b) {
                return a->getOrder() < b->getOrder();
            });
        }
    }

    void EventBus::postEvent(IEvent* event) {
        if (!event) return;

        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push_back(event);

        glfwPostEmptyEvent();
    }

    bool EventBus::dispatch() {
        std::vector<IEvent*> processingQueue;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (eventQueue.empty()) return false;
            processingQueue.swap(eventQueue);
        }

        std::lock_guard<std::mutex> lock(registerMutex);

        for (auto* event : processingQueue) {
            const void* type = event->getEventType();
            if (subscriberMap.contains(type)) {
                for (auto* handler : subscriberMap[type]) {
                    // 支持取消逻辑
                    if (event->getIsCancelled()) break;
                    handler->execute(event);
                }
            }
            delete event;
        }

        return true;
    }

    void EventBus::removeListener(IListener* listener) {
        if (!listener) return;

        std::lock_guard<std::mutex> lock(registerMutex);

        for (auto* handler : listener->getHandlers()) {
            const void* typeID = handler->getEventType();

            if (subscriberMap.contains(typeID)) {
                auto& vec = subscriberMap[typeID];
                std::erase(vec, handler);

                if (vec.empty()) subscriberMap.erase(typeID);
            }
        }

        std::erase(registeredListeners, listener);

        delete listener;
    }

    void EventBus::shutdown() {
        std::lock_guard<std::mutex> lock_r(registerMutex);
        std::lock_guard<std::mutex> lock_q(queueMutex);
        for (auto* e : eventQueue) delete e;
        eventQueue.clear();

        for (IListener* listener : registeredListeners) {
            delete listener;
        }
    }

    EventBus::~EventBus() {
        shutdown();
    }
}