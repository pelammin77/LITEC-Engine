#include <stddef.h>  
#include <time.h>
#include "EngineEvent.h"

void EngineEvent_Init(EngineEvent* event, EventType type, EventCategory category) {
    if (event != NULL) {
        Event_Init(&event->base_event, type, category);
        // Alusta muut jäsenet tarpeen mukaan...
    }
}

int EngineEvent_GetErrorCode(const EngineEvent* event) {
    return event->errorCode;
}

void EngineEvent_SetErrorCode(EngineEvent* event, int errorCode) {
    event->errorCode = errorCode;
}

time_t EngineEvent_GetTimestamp(const EngineEvent* event) {
    return event->timestamp;
}

void EngineEvent_SetTimestamp(EngineEvent* event, time_t timestamp) {
    event->timestamp = timestamp;
}