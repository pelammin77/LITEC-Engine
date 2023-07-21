
#include"WindowEvent.h"
#include<stdlib.h>



void WindowEvent_Init(WindowEvent* event, EventType type, EventCategory category) {
    if (event != NULL) {
        Event_Init(&event->base_event, type, category);
    }
}

void WindowEvent_SetSize(WindowEvent* event, int width, int height) {
    if (event != NULL) {
        event->width = width;
        event->height = height;
    }
}

void WindowEvent_GetSize(const WindowEvent* event, int* width, int* height) {
    if (event != NULL) {
        *width = event->width;
        *height = event->height;
    }
}

void WindowEvent_SetFocus(WindowEvent* event, int focus) {
    if (event != NULL) {
        event->focus = focus;
    }
}

int WindowEvent_GetFocus(const WindowEvent* event) {
    if (event != NULL) {
        return event->focus;
    }
    return 0; // returns 0 if event is NULL
}