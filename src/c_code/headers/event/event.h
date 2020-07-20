
#include <vector>
#include <map>
#include <memory>

enum class EventType
{
    None = 0,
    SceneManagerInitialized,
    WindowCreated
};

class IEvent
{
public:
    virtual const enum EventType GetType() const = 0;
};

template <typename... args>
class Event : public IEvent
{
    private:
    //Event identifier
    EventType type;
    //Event callback - can't be changed inside event.
    const std::function<void(args...)>  callback;
public:

    //Ctor & Dtor
    //template< typename T_CB >
    explicit Event(EventType t, const std::function<void(args...)>  &cb) : type(t), callback(cb) {}
    ~Event() {}

    //Accessors
    virtual const EventType GetType() const override { return this->type; }

    //Methods
    void trigger(args... a) { this->callback(a...); }
};

class EventDispatcher
{
public:
    EventDispatcher() {}
    ~EventDispatcher()
    {
        for (auto el : _eventList)
        {
            for (auto e : el.second)
                delete e;
        }
    }

    void registerEvent(IEvent *event)
    {
        if (event)
            _eventList[event->GetType()].push_back(event);
    }

    template <typename... _args>
    void dispatchEvent(EventType eventType, _args... a)
    {
        auto it_eventList = _eventList.find(eventType);
        if (it_eventList == _eventList.end())
            return;
        for (auto ie : it_eventList->second)
        {
            if (Event<_args...> *event = dynamic_cast<Event<_args...> *>(ie))
                event->trigger(a...);
        }
    }

private:
    std::map<EventType, std::vector<IEvent *>> _eventList;
};