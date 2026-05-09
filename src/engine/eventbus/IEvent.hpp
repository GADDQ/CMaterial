//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_IEVENT_H
#define CMATERIAL_IEVENT_H


namespace cmaterial::event {
    /**
     * @brief The base of the Event.
     * @details You want to tell others something has happened, and this is the tool to make a message about
     * "something".
     *
     * @details --- Require Macro ---
     * @details @code REGISTEREVENT(EventClass)@endcode : You must write it in the first line of the class.
     *
     * @details --- Property ---
     * @details @code any ...@endcode : These are properties you want to include in the message. You can add them by
     * yourself.
     *
     * @details --- Advanced ---
     * @details You can use @code struct@endcode to make an Event, because most of the time you may just want to send a
     * message and give away some properties but don't want to give functions in the Event.
     *
     * @details --- DANGER ZONE ---
     * @details @code bool isCancelled@endcode : Does the Event need to be cancelled? You shouldn't modify this because
     * this should be modified by the Listener.
     *
     * @warning You should extend it to make a custom Event. NEVER USE THE INTERFACE DIRECTLY!
     */
    class IEvent {
    public:
        virtual ~IEvent() = default;
        virtual const void* getEventType() const = 0;

        /**
         * @brief Does the Event need to be cancelled?
         * @details In most cases, you won't need to change this.
         */
        bool isCancelled = false;

#define REGISTEREVENT(T)                                                                                               \
        static const void *getStaticType() {                                                                           \
            static int dummy;                                                                                          \
            return &dummy;                                                                                             \
        }                                                                                                              \
        const void *getEventType() const override {                                                                    \
            return getStaticType();                                                                                    \
        }
    };
}



#endif //CMATERIAL_IEVENT_H
