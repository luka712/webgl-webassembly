#pragma once

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
    EventType type;
    const std::function<void(args...)> callback;

public:
    explicit Event(EventType t, const std::function<void(args...)> &cb) : type(t), callback(cb) {}

    virtual const EventType GetType() const override { return this->type; }
    void trigger(args... a) { this->callback(a...); }
};

class EventDispatcher
{
private:
    std::map<EventType, std::vector<IEvent *>> eventList;

public:
    EventDispatcher() {}
    ~EventDispatcher()
    {
        // for(auto &[key, events] : eventList)
        // {
        //     for (auto e : events)
        //     {
        //        //  delete e;
        //     }
        //     events.empty();
        // }
        // eventList.empty();
    }

    void registerEvent(IEvent *event)
    {
        if (event)
            eventList[event->GetType()].push_back(event);
    }

    template <typename... args>
    void dispatchEvent(EventType eventType, args... a)
    {
        auto it = eventList.find(eventType);
        if (it == eventList.end())
            return;

        for (auto ie : it->second)
        {
            if (Event<args...> *event = dynamic_cast<Event<args...> *>(ie))
                event->trigger(a...);
        }
    }
};