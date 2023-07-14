#ifndef EVENT_H
#define EVENT_H

typedef enum {
    EVENT_NONE = 0,
    EVENT_WINDOW_OPEN,
    EVENT_WINDOW_CLOSE, 
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_FOCUS,
    EVENT_WINDOW_LOST_FOCUS,
    EVENT_KEY_PRESSED,
    EVENT_KEY_RELEASED,
    EVENT_MOUSE_BUTTON_PRESSED,
    EVENT_MOUSE_BUTTON_RELEASED,
    EVENT_MOUSE_MOVED,
    EVENT_MOUSE_SCROLLED,
    EVENT_ENGINE_INITIALIZED,
    EVENT_ENGINE_SHUTDOWN,
    EVENT_ENGINE_PAUSED,
    EVENT_ENGINE_RESUMED,
    EVENT_ENGINE_TICK,
    EVENT_ENGINE_UPDATE,
    EVENT_ENGINE_ERROR,
    EVENT_ENGINE_RENDER,
    // lisää event-tyyppejä tarpeen mukaan
} EventType;


typedef enum {
    CATEGORY_NONE = 0,
    CATEGORY_WINDOW,
    CATEGORY_INPUT,
    CATEGORY_ENGINE,
    // lisää kategorioita tarpeen mukaan
} EventCategory;



typedef struct {
    EventType type;
    EventCategory category;
    void *data;

    // mahdollisesti muita tietoja tapahtumasta
} Event;


void Event_Init(Event* event, EventType type);
EventType Event_GetType(const Event* event) ;
void Event_SetType(Event* event, EventType type); 
void Event_SetData(Event* event, void* data);
void* Event_GetData(Event* event);


// muut funktion määritelmät tähän

#endif // EVENT_H
