//EventDispatcher.h

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H
#include <stdbool.h>
#include "Event.h"

// Alustaa EventDispatcherin
void EventDispatcher_Init();

// Lisää tapahtumankuuntelijan EventDispatcheriin. EventListener on funktio, joka ottaa parametrina Event*.
// Tässä voisi olla myös jokin tapahtumatyyppikohtainen kuuntelija, jolloin kuuntelija saisi vain tietyn tyyppisiä tapahtumia.
void EventDispatcher_AddListener(void (*EventListener)(Event*));

// Poistaa tapahtumankuuntelijan EventDispatcherista.
void EventDispatcher_RemoveListener(void (*EventListener)(Event*));

// Lähettää tapahtuman eteenpäin kaikille tapahtumankuuntelijoille.
void EventDispatcher_DispatchEvent(Event* event);

// Rekisteröi käsittelijän tietyn kategorian tapahtumille.
void EventDispatcher_RegisterHandler(EventCategory category, void (*EventHandler)(Event*));


bool EventDispatcher_IsInitialized();
bool EventDispatcher_HasRegisteredHandlers();

#endif // EVENTDISPATCHER_H
