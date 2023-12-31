//EventDispatcher.c


#include <stdlib.h>
#include "EventDispatcher.h"
#include <stdbool.h>
#include<stdio.h>


int isInitialized = 0;
// Taulukko funktio-osoittimille
static void (**EventListeners)(Event*) = NULL;
// Taulukko tapahtumakategorioille
static EventCategory *EventCategories = NULL;
// Taulukon koko


static size_t listenerCount;

// Taulukon kapasiteetti
static size_t capacity;

void EventDispatcher_Init() {
    EventListeners = NULL;
    EventCategories = NULL;
    listenerCount = 0;
    capacity = 0;
    isInitialized = 1;
}

void EventDispatcher_AddListener(void (*EventListener)(Event*)) {
    
    // Tarkista, onko kapasiteetti riittävä. Jos ei, kasvatetaan sitä.
    if (listenerCount >= capacity) {
        capacity = capacity == 0 ? 1 : capacity * 2; // Käytä geometrista kasvua: jos kapasiteetti on 0, aseta se 1:ksi, muutoin tuplaa se.
        EventListeners = realloc(EventListeners, capacity * sizeof(*EventListeners));
        EventCategories = realloc(EventCategories, capacity * sizeof(*EventCategories));
    }

    // Lisätään uusi kuuntelija taulukkoon
    EventListeners[listenerCount] = EventListener;
    listenerCount++;
    
}

// ... Loput koodista menee tässä. Muista huolehtia EventDispatcher_RegisterHandler:n muokkauksesta samalla tavalla kuin EventDispatcher_AddListener.

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
    // Tarkista onko isInitialized lippu asetettu ennen kuin jatkat
    if (!isInitialized) {
        printf("Error: Attempted to dispatch an event before initialization was complete.\n");
        return;
    }
    for (size_t i = 0; i < listenerCount; i++) {
        if(EventCategories[i] == event->category){
            EventListeners[i](event);
        }
    }
 
}
void EventDispatcher_RegisterHandler(EventCategory category, void (*EventHandler)(Event*)) {
   

    // Lisätään uusi käsittelijä ja sen kategoria taulukkoihin
    void* tempListeners = realloc(EventListeners, (listenerCount + 1) * sizeof(*EventListeners));
    if (tempListeners != NULL) {
        EventListeners = tempListeners;
        EventListeners[listenerCount] = EventHandler;
        
    }
    else {
        printf("Memory error!");
        // Käsittely, jos realloc epäonnistuu. Esimerkiksi vapauta muistia tai lopeta ohjelma.
    }

    void* tempCategories = realloc(EventCategories, (listenerCount + 1) * sizeof(*EventCategories));
    if (tempCategories != NULL) {
        EventCategories = tempCategories;
        EventCategories[listenerCount] = category;
    }
    else {
        // Käsittely, jos realloc epäonnistuu.
    }

    listenerCount++;
    // Tulostetaan kuuntelijoiden ja kategorioiden taulukot
    
    
   
}



// EventDispatcher.c
bool EventDispatcher_IsInitialized() {
    // Voit tarkistaa, onko EventDispatcher alustettu, esim. tarkistamalla,
    // onko jokin sen komponentti, kuten EventListeners-taulukko, määritetty.
    // Oletetaan tässä, että taulukon pitäisi olla NULL ennen alustusta.
    return EventListeners != NULL;
}

bool EventDispatcher_HasRegisteredHandlers() {
    // Tarkistetaan, onko ainakin yksi käsittelijä rekisteröity.
    return listenerCount > 0;
}

