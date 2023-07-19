

#include <LITEC.h>
#include<stdio.h>
#include "Events/EventDispatcher.h"

// Tapahtumankäsittelijä, joka kutsutaan, kun moottori on käynnistetty.
void HandleEngineInitialized(Event* event) {
    printf("Engine Initialized event received in Sandbox\n");
}




int main() {
    // Alusta LITEC-kirjasto ja  EventDispatcher
    EventDispatcher_Init();
        EventDispatcher_RegisterHandler(EVENT_ENGINE_INITIALIZED, HandleEngineInitialized);
        if (EventDispatcher_IsInitialized() && EventDispatcher_HasRegisteredHandlers()) 
        {
            printf("Initlize engine\n");
            LITEC_Init();

             // Luo ikkuna
        LITEC_Window* window = LITEC_CreateWindow("My Game Window", 800, 600);
        if (window == NULL) 
        {
            printf("Window creation failed!\n");
            return 1;
        }




        }
    // Pelisilmukka
    while (LITEC_Running()) {
        
        //LITEC_HandleInput();
        LITEC_Update();
        //LITEC_Render();
    }

    // Siivoa j�ljet
    LITEC_Shutdown();

    return 0;
}