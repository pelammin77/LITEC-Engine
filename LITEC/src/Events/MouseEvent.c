#include "MouseEvent.h"

void MouseMovedEvent_Init(MouseMovedEvent* event, double x, double y)
{
    Event_Init(&event->base_event, EVENT_MOUSE_MOVED, CATEGORY_INPUT);
    event->x = x;
    event->y = y;
}
void MouseButtonPressedEvent_Init(MouseButtonEvent* event, int button, double x, double y)
{
    Event_Init(&event->base_event, EVENT_MOUSE_BUTTON_PRESSED, CATEGORY_INPUT);
    event->button = button;
    event->x = x;
    event->y = y;
}

void MouseButtonReleasedEvent_Init(MouseButtonEvent* event, int button, double x, double y)
{
    Event_Init(&event->base_event, EVENT_MOUSE_BUTTON_RELEASED, CATEGORY_INPUT);
    event->button = button;
    event->x = x;
    event->y = y;
}

void MouseScrolledEvent_Init(MouseScrolledEvent* event, double xOffset, double yOffset)
{
    Event_Init(&event->base_event, EVENT_MOUSE_SCROLLED, CATEGORY_INPUT);
    event->xOffset = xOffset;
    event->yOffset = yOffset;
}