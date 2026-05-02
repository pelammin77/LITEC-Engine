// LITEC.c

#include <stdio.h>

#include "LITEC.h"
#include "Logger.h"

#include "Events/EngineEvent.h"
#include "Events/WindowEvent.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "LayerStack.h"
#include "Gui/GuiLayer.h"

//#include "cglm/cglm.h"
//#include "LitecMath.h"
//#include "nuklear.h"


static int running = 1;
static LITEC_Window* window = NULL;

static LayerStack layerStack;
static Layer* guiLayer = NULL;


void handleWindowOpenEvent(Event* event)
{
    if (event->type == EVENT_WINDOW_OPEN)
    {
        print_info("LITEC Engine created new window");
    }
}


void handleWindowResizeEvent(Event* event)
{
    if (event->type == EVENT_WINDOW_RESIZE)
    {
        WindowEvent* windowEvent = (WindowEvent*)event;

        char buffer[128];
        snprintf(buffer, sizeof(buffer),
            "Window resized: width=%d, height=%d",
            windowEvent->width, windowEvent->height);

        print_info(buffer);
    }
}


void handleWindowCloseEvent(Event* event)
{
    if (event->type == EVENT_WINDOW_CLOSE)
    {
        print_info("Closing window");
        running = 0;
    }
}


void handleKeyPressedEvent(const Event* event)
{
    if (event->type == EVENT_KEY_PRESSED)
    {
        KeyPressedEventData* data = (KeyPressedEventData*)event->data;

        print_info("Key pressed event");

        if (data)
        {
            printf("Key code: %d, repeat count: %d\n",
                data->keyCode,
                data->repeatCount);
        }
    }
}


void handleKeyReleasedEvent(const Event* event)
{
    if (event->type == EVENT_KEY_RELEASED)
    {
        KeyReleasedEventData* data = (KeyReleasedEventData*)event->data;

        print_info("Key released event");

        if (data)
        {
            printf("Key code: %d\n", data->keyCode);
        }
    }
}


void handleMouseMovedEvent(const Event* event)
{
    if (event->type == EVENT_MOUSE_MOVED)
    {
        const MouseMovedEvent* mouseEvent = (const MouseMovedEvent*)event;

        print_info("Mouse moved event");

        printf("Mouse position: x=%f, y=%f\n",
            mouseEvent->x,
            mouseEvent->y);
    }
}


void handleMouseButtonPressedEvent(const Event* event)
{
    if (event->type == EVENT_MOUSE_BUTTON_PRESSED)
    {
        const MouseButtonEvent* mouseEvent = (const MouseButtonEvent*)event;

        print_info("Mouse button pressed event");

        printf("Mouse button: %d, x=%f, y=%f\n",
            mouseEvent->button,
            mouseEvent->x,
            mouseEvent->y);
    }
}


void handleMouseButtonReleasedEvent(const Event* event)
{
    if (event->type == EVENT_MOUSE_BUTTON_RELEASED)
    {
        const MouseButtonEvent* mouseEvent = (const MouseButtonEvent*)event;

        print_info("Mouse button released event");

        printf("Mouse button: %d, x=%f, y=%f\n",
            mouseEvent->button,
            mouseEvent->x,
            mouseEvent->y);
    }
}


void handleMouseScrolledEvent(const Event* event)
{
    if (event->type == EVENT_MOUSE_SCROLLED)
    {
        const MouseScrolledEvent* mouseEvent = (const MouseScrolledEvent*)event;

        print_info("Mouse scrolled event");

        printf("Mouse scroll: xOffset=%f, yOffset=%f\n",
            mouseEvent->xOffset,
            mouseEvent->yOffset);
    }
}


void LITEC_Init(const char* title, int width, int height)
{
    init_logger();
    EventDispatcher_Init();
    LayerStack_Init(&layerStack);

    print_info("LITEC engine is starting. Welcome!\n");

    EventDispatcher_RegisterHandler(CATEGORY_WINDOW, handleWindowResizeEvent);
    EventDispatcher_RegisterHandler(CATEGORY_WINDOW, handleWindowOpenEvent);
    EventDispatcher_RegisterHandler(CATEGORY_WINDOW, handleWindowCloseEvent);

    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleKeyPressedEvent);
    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleKeyReleasedEvent);
    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleMouseMovedEvent);
    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleMouseButtonPressedEvent);
    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleMouseButtonReleasedEvent);
    EventDispatcher_RegisterHandler(CATEGORY_INPUT, handleMouseScrolledEvent);

    window = LITEC_CreateWindow(title, width, height);

    if (window == NULL)
    {
        print_fatal_error("Window creation failed!");
        return;
    }

    guiLayer = GuiLayer_Create();

    if (guiLayer != NULL)
    {
        LayerStack_PushOverlay(&layerStack, guiLayer);

        if (guiLayer->OnAttach != NULL)
        {
            guiLayer->OnAttach(guiLayer);
        }
    }
}


int LITEC_Running()
{
    return running;
}


void LITEC_HandleInput()
{
    // Tähän tulee myöhemmin syötteiden käsittelykoodi.
}


void LITEC_Update()
{
    glfwPollEvents();

    Window_Update(window);

    LITEC_HandleInput();

    /*
        Tässä vaiheessa deltaTime on vielä 0.0f.
        Myöhemmin tähän voidaan tehdä oikea ajastus.
    */
    float deltaTime = 0.0f;

    for (unsigned int i = 0; i < LayerStack_GetCount(&layerStack); i++)
    {
        Layer* layer = LayerStack_GetLayer(&layerStack, i);

        if (layer != NULL && layer->OnUpdate != NULL)
        {
            layer->OnUpdate(layer, deltaTime);
        }
    }

    // Tähän tulee myöhemmin pelin päivityskoodi.
}


void LITEC_Render()
{
    Window_Render(window);
    glfwSwapBuffers(window->glfwWindow);
}


void LITEC_Shutdown()
{
    EngineEvent engineShutdownEvent;
    EngineEvent_Init(&engineShutdownEvent, EVENT_ENGINE_SHUTDOWN, CATEGORY_ENGINE);

    EventDispatcher_DispatchEvent(&engineShutdownEvent.base_event);

    if (guiLayer != NULL)
    {
        LayerStack_RemoveOverlay(&layerStack, guiLayer);
        GuiLayer_Destroy(guiLayer);
        guiLayer = NULL;
    }

    LayerStack_Clear(&layerStack);

    if (window != NULL)
    {
        LITEC_DestroyWindow(window);
        window = NULL;
    }

    print_info("LITEC engine is shutting down. Goodbye!\n");

    running = 0;

    close_logger();
}


LITEC_Window* LITEC_CreateWindow(const char* title, int width, int height)
{
    LITEC_Window* newWindow = Window_Create(width, height, title);

    if (newWindow != NULL)
    {
        WindowEvent event;
        WindowEvent_Init(&event, EVENT_WINDOW_OPEN, CATEGORY_WINDOW);
        EventDispatcher_DispatchEvent(&event.base_event);
    }

    return newWindow;
}


void LITEC_DestroyWindow(LITEC_Window* window)
{
    Window_Destroy(window);
}