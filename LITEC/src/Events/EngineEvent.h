#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H
#include <time.h>
#include "Event.h"

typedef struct {
    Event base_event; // Perii Event-rakenteen
    // Moottorikohtaiset kentät
    int errorCode; // Virhekoodi EVENT_ENGINE_ERROR:lle
    double timestamp; // Aikaleima EVENT_ENGINE_TICK:lle ja EVENT_ENGINE_UPDATE:lle
    // Lisää kenttiä tarpeen mukaan
    // functions 



} EngineEvent;
void EngineEvent_Init(EngineEvent* event, EventType type, EventCategory category);
int EngineEvent_GetErrorCode(const EngineEvent* event);
void EngineEvent_SetErrorCode(EngineEvent* event, int errorCode);
time_t EngineEvent_GetTimestamp(const EngineEvent* event);
void EngineEvent_SetTimestamp(EngineEvent* event, time_t timestamp);







#endif // ENGINEEVENT_H