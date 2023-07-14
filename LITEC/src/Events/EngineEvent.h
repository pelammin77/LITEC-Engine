#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H

#include "Event.h"

typedef struct {
    Event base; // Perii Event-rakenteen
    // Moottorikohtaiset kentät
    int errorCode; // Virhekoodi EVENT_ENGINE_ERROR:lle
    double timestamp; // Aikaleima EVENT_ENGINE_TICK:lle ja EVENT_ENGINE_UPDATE:lle
    // Lisää kenttiä tarpeen mukaan
} EngineEvent;





#endif // ENGINEEVENT_H