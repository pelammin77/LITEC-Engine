#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.h"

typedef struct {
    Event base_event;
    double x;
    double y;
} MouseMovedEvent;

typedef struct {
    Event base_event;
    int button;
    double x;
    double y;
} MouseButtonEvent;

typedef struct {
    Event base_event;
    double xOffset;
    double yOffset;
} MouseScrolledEvent;

void MouseMovedEvent_Init(MouseMovedEvent* event, double x, double y);
void MouseButtonPressedEvent_Init(MouseButtonEvent* event, int button, double x, double y);
void MouseButtonReleasedEvent_Init(MouseButtonEvent* event, int button, double x, double y);
void MouseScrolledEvent_Init(MouseScrolledEvent* event, double xOffset, double yOffset);

#endif