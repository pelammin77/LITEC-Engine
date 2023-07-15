#include <stdlib.h>
#include "EventDispatcher.h"

// Taulukko funktio-osoittimille
static void (**EventListeners)(Event*) = NULL;
// Taulukon koko
static size_t listenerCount = 0;

void EventDispatcher_Init() {
    EventListeners = NULL;
    listenerCount = 0;
}

void EventDispatcher_AddListener(void (*EventListener)(Event*)) {
    // Lisätään uusi kuuntelija taulukkoon
    EventListeners = realloc(EventListeners, (listenerCount + 1) * sizeof(*EventListeners));
    EventListeners[listenerCount] = EventListener;
    listenerCount++;
}

void EventDispatcher_RemoveListener(void (*EventListener)(Event*)) {
    // Etsitään kuuntelija taulukosta ja poistetaan se
    for (size_t i = 0; i < listenerCount; i++) {
        if (EventListeners[i] == EventListener) {
            EventListeners[i] = EventListeners[listenerCount - 1];
            EventListeners = realloc(EventListeners, (listenerCount - 1) * sizeof(*EventListeners));
            listenerCount--;
            break;
        }
    }
}

void EventDispatcher_DispatchEvent(Event* event) {
    // Lähetetään tapahtuma kaikille kuuntelijoille
    for (size_t i = 0; i < listenerCount; i++) {
        EventListeners[i](event);
    }
}
