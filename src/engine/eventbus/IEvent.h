//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_IEVENT_H
#define CMATERIAL_IEVENT_H


namespace cmaterial::event {
    class IEvent {
    public:
        virtual ~IEvent() = default;
        virtual const void* getEventType() const = 0;

        bool getIsCancelled() const;

    protected:
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
