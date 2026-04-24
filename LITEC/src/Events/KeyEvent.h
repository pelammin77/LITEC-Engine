#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event.h"

typedef struct {
    int keyCode;
    int repeatCount;
} KeyPressedEventData;

typedef struct {
    int keyCode;
} KeyReleasedEventData;

void KeyEvent_CreatePressed(Event* event, KeyPressedEventData* data, int keyCode, int repeatCount);
void KeyEvent_CreateReleased(Event* event, KeyReleasedEventData* data, int keyCode);

#endif