#include "KeyEvent.h"

void KeyEvent_CreatePressed(Event* event, KeyPressedEventData* data, int keyCode, int repeatCount)
{
    data->keyCode = keyCode;
    data->repeatCount = repeatCount;

    Event_Init(event, EVENT_KEY_PRESSED, CATEGORY_INPUT);
    Event_SetData(event, data);
}

void KeyEvent_CreateReleased(Event* event, KeyReleasedEventData* data, int keyCode)
{
    data->keyCode = keyCode;

    Event_Init(event, EVENT_KEY_RELEASED, CATEGORY_INPUT);
    Event_SetData(event, data);
}