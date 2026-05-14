//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_ILISTENER_H
#define CMATERIAL_ILISTENER_H


#include <vector>
#include <type_traits>

namespace cmaterial::event {
    class IEvent;

    class IHandler {
    public:
        enum Order {
            FIRST = 0,
            DEFAULT = 1,
            LAST = 2
        };

        virtual ~IHandler() = default;
        virtual void execute(IEvent* e) = 0;
        virtual const void* getEventType() const = 0;
        virtual Order getOrder() const = 0;
    };

    template<typename EventT, typename FuncT>
    class LambdaHandler : public IHandler {
        FuncT func;
        Order order;
    public:
        LambdaHandler(FuncT f, Order o) : func(std::move(f)), order(o) {}
        void execute(IEvent* e) override { func(static_cast<EventT*>(e)); }
        const void* getEventType() const override { return EventT::getStaticType(); }
        Order getOrder() const override { return order; }
    };

    /**
     * @brief The base of the Listener.
     * @details You want to do something after it happens, and this is the tool to make it.
     *
     * @details --- Require Macro ---
     * @details @code EVENTHANDLER(EventClass, FunctionName)@endcode : You must write it before the function you want to
     * make a Listener.
     * @details @code EVENTHANDLER(EventClass, FunctionName, Order)@endcode : Same as the last one, but you can use the
     * Order property to control the Listeners' execution order. @code HIGH@endcode means execute as early as possible,
     * @code LOW@endcode means the opposite, @code DEFAULT@endcode is completely the same as the last macro.
     *
     * @details --- Tips ---
     * @details Some Events will include some useful properties to use, you can get them like this:
     * @details @code event->property@endcode
     * @details You could implement several functions and mark them with different @code EVENTHANDLER@endcode to listen
     * to different events in a single Listener.
     * @details (e.g. @code onButtonClicked()@endcode + @code onButtonHover()@endcode -> @code ButtonListener@endcode )
     *
     * @details --- Advanced ---
     * @details You could use @code event->isCancelled = true@endcode to cancel an event. This will make lower-order
     * Listeners stop doing their work.
     * @details BUT, if two Listeners have the same Order, the first loaded Listener will cancel the second one.
     * @details In most cases, you won't need this, because for GUI development, cancellation will usually not happen.
     * @details UNLESS you use my EventBus to connect a custom backend (e.g. Network). But don't get me wrong — this is
     * a usage I fully endorse, and it's even expected.
     *
     * @warning You should extend it to make a custom Listener. NEVER USE THE INTERFACE DIRECTLY!
     */
    class IListener {
    public:
        using Order = IHandler::Order;

        virtual ~IListener();

        const std::vector<IHandler*>& getHandlers() const;
        void _add_handler(IHandler* h);

        template<typename EventT, typename FuncT>
        int _do_bind(FuncT func, Order o) {
            this->_add_handler(new LambdaHandler<EventT, FuncT>(std::move(func), o));
            return 0;
        }

    protected:
        std::vector<IHandler*> handlers;
    };
}

#define GET_EH_MACRO(_1, _2, _3, NAME, ...) NAME
#define EXPAND(x) x

#define EVENTHANDLER_2(EventT, MethodName)                                                                             \
    int _h_##MethodName =                                                                                              \
            this->_do_bind<EventT>([this](EventT *e) { this->MethodName(e); }, cmaterial::event::IHandler::DEFAULT);

#define EVENTHANDLER_3(EventT, MethodName, OrderVal)                                                                   \
    int _h_##MethodName = this->_do_bind<EventT>([this](EventT *e) { this->MethodName(e); }, OrderVal);

#define EVENTHANDLER(...) EXPAND(GET_EH_MACRO(__VA_ARGS__, EVENTHANDLER_3, EVENTHANDLER_2)(__VA_ARGS__))


#endif // CMATERIAL_ILISTENER_H
