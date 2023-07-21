#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event.h"


typedef struct {
    Event base_event;
    int width;
    int height;
    int focus;
} WindowEvent;

void WindowEvent_Init(WindowEvent* event, EventType type, EventCategory category);
void WindowEvent_SetSize(WindowEvent* event, int width, int height);
void WindowEvent_GetSize(const WindowEvent* event, int* width, int* height);
void WindowEvent_SetFocus(WindowEvent* event, int focus);
int WindowEvent_GetFocus(const WindowEvent* event);



#endif