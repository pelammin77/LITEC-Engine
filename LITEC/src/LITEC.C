// LITEC.c



#include <stdio.h>
#include "LITEC.h"
#include "Logger.h"
#include "Events/EngineEvent.h"
#include "Events/EventDispatcher.h"

static int running = 1;

void LITEC_Init() {
    init_logger();
    print_info("LITEC engine is starting. Welcome!\n");
    // Luo EngineEvent
    EngineEvent engineStartEvent;
    EngineEvent_Init(&engineStartEvent, EVENT_ENGINE_INITIALIZED, CATEGORY_ENGINE);

    // Lähetä tapahtuma järjestelmässä eteenpäin
    EventDispatcher_DispatchEvent(&engineStartEvent.base_event);

}

int LITEC_Running() {
    return running;
}

void LITEC_HandleInput() {
    // T�h�n tulee my�hemmin sy�tteiden k�sittelykoodi.
}

void LITEC_Update() {
    // T�h�n tulee my�hemmin pelin p�ivityskoodi.
}

void LITEC_Render() {
    // T�h�n tulee my�hemmin piirtokoodi.
}

void LITEC_Shutdown() {
    // Luo EngineEvent
    EngineEvent engineShutdownEvent;
    EngineEvent_Init(&engineShutdownEvent, EVENT_ENGINE_SHUTDOWN, CATEGORY_ENGINE);
    
    // Lähetä tapahtuma järjestelmässä eteenpäin
    EventDispatcher_DispatchEvent(&engineShutdownEvent.base_event);

    print_info("LITEC engine is shutting down. Goodbye!\n");
    running = 0;
    close_logger();

}
