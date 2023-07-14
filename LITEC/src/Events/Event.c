// Event.c

#include "Event.h"
#include <stdlib.h>

void Event_Init(Event* event, EventType type) {
    if (event != NULL) {
        event->type = type;
        event->data = NULL; // Alustetaan data NULL:ksi. Voit muuttaa tätä, jos tarpeen.
    }
}

EventType Event_GetType(const Event* event) {
    return event->type;
}

void Event_SetType(Event* event, EventType type) {
    event->type = type;
}





void Event_SetData(Event* event, void* data) {
    if (event != NULL) {
        event->data = data;
    }
}

void* Event_GetData(Event* event) {
    if (event != NULL) {
        return event->data;
    }
    return NULL;
}


// Muita funktioita voivat olla esim. Event_SetData, Event_GetData jne.
