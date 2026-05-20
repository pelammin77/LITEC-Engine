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
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

//#include "cglm/cglm.h"
//#include "LitecMath.h"
//#include "nuklear.h"


static int running = 1;
static LITEC_Window* window = NULL;

static LayerStack layerStack;
static Layer* guiLayer = NULL;


static void LITEC_DispatchEventToLayers(Event* event)
{
    if (event == NULL)
    {
        return;
    }

    unsigned int count = LayerStack_GetCount(&layerStack);

    if (count == 0)
    {
        return;
    }

    /*
        Eventit välitetään lopusta alkuun.

        Tämä tarkoittaa:
        GuiLayer / overlay saa eventin ensin.
        GameLayer saa eventin myöhemmin.
    */
    for (int i = (int)count - 1; i >= 0; i--)
    {
        Layer* layer = LayerStack_GetLayer(&layerStack, (unsigned int)i);

        if (layer != NULL && layer->OnEvent != NULL)
        {
            layer->OnEvent(layer, event);

            if (event->handled)
            {
                break;
            }
        }
    }
}


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
        snprintf(
            buffer,
            sizeof(buffer),
            "Window resized: width=%d, height=%d",
            windowEvent->width,
            windowEvent->height
        );

        print_info(buffer);

        LITEC_DispatchEventToLayers(event);
    }
}


void handleWindowCloseEvent(Event* event)
{
    if (event->type == EVENT_WINDOW_CLOSE)
    {
        print_info("Closing window");
        running = 0;

        LITEC_DispatchEventToLayers(event);
    }
}


void handleKeyPressedEvent(Event* event)
{
    if (event->type == EVENT_KEY_PRESSED)
    {
        KeyPressedEventData* data = (KeyPressedEventData*)event->data;

        print_info("Key pressed event");

        if (data)
        {
            printf(
                "Key code: %d, repeat count: %d\n",
                data->keyCode,
                data->repeatCount
            );
        }

        LITEC_DispatchEventToLayers(event);
    }
}


void handleKeyReleasedEvent(Event* event)
{
    if (event->type == EVENT_KEY_RELEASED)
    {
        KeyReleasedEventData* data = (KeyReleasedEventData*)event->data;

        print_info("Key released event");

        if (data)
        {
            printf("Key code: %d\n", data->keyCode);
        }

        LITEC_DispatchEventToLayers(event);
    }
}


void handleMouseMovedEvent(Event* event)
{
    if (event->type == EVENT_MOUSE_MOVED)
    {
        const MouseMovedEvent* mouseEvent = (const MouseMovedEvent*)event;

        print_info("Mouse moved event");

        printf(
            "Mouse position: x=%f, y=%f\n",
            mouseEvent->x,
            mouseEvent->y
        );

        LITEC_DispatchEventToLayers(event);
    }
}


void handleMouseButtonPressedEvent(Event* event)
{
    if (event->type == EVENT_MOUSE_BUTTON_PRESSED)
    {
        const MouseButtonEvent* mouseEvent = (const MouseButtonEvent*)event;

        print_info("Mouse button pressed event");

        printf(
            "Mouse button: %d, x=%f, y=%f\n",
            mouseEvent->button,
            mouseEvent->x,
            mouseEvent->y
        );

        LITEC_DispatchEventToLayers(event);
    }
}


void handleMouseButtonReleasedEvent(Event* event)
{
    if (event->type == EVENT_MOUSE_BUTTON_RELEASED)
    {
        const MouseButtonEvent* mouseEvent = (const MouseButtonEvent*)event;

        print_info("Mouse button released event");

        printf(
            "Mouse button: %d, x=%f, y=%f\n",
            mouseEvent->button,
            mouseEvent->x,
            mouseEvent->y
        );

        LITEC_DispatchEventToLayers(event);
    }
}


void handleMouseScrolledEvent(Event* event)
{
    if (event->type == EVENT_MOUSE_SCROLLED)
    {
        const MouseScrolledEvent* mouseEvent = (const MouseScrolledEvent*)event;

        print_info("Mouse scrolled event");

        printf(
            "Mouse scroll: xOffset=%f, yOffset=%f\n",
            mouseEvent->xOffset,
            mouseEvent->yOffset
        );

        LITEC_DispatchEventToLayers(event);
    }
}


void LITEC_Init(const char* title, int width, int height)
{
    init_logger();
    EventDispatcher_Init();
    LayerStack_Init(&layerStack);
    Input_Init();

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

    guiLayer = GuiLayer_Create(window->glfwWindow);

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
    /*
        Väliaikainen polling-testi.

        Tässä käytetään nyt Litecin omia input-koodeja.
        GLFW-koodit muunnetaan Litec-koodeiksi Platform/GLFW/GLFWInputMap.c:ssä.
    */

    if (Input_IsKeyDown(LITEC_KEY_LEFT_CONTROL))
    {
        print_info("Polling: left CTRL is down");
    }

    if (Input_IsKeyPressed(LITEC_KEY_S))
    {
        print_info("Polling: S was pressed this frame");
    }

    if (
        Input_IsKeyDown(LITEC_KEY_LEFT_CONTROL) &&
        Input_IsKeyPressed(LITEC_KEY_S)
        )
    {
        print_info("Polling: CTRL + S detected");
    }

    if (Input_IsMouseButtonDown(LITEC_MOUSE_BUTTON_LEFT))
    {
        print_info("Polling: left mouse button is down");
    }

    if (Input_IsMouseButtonPressed(LITEC_MOUSE_BUTTON_LEFT))
    {
        print_info("Polling: left mouse button pressed this frame");
    }

    if (Input_IsMouseButtonReleased(LITEC_MOUSE_BUTTON_LEFT))
    {
        print_info("Polling: left mouse button released this frame");
    }

    if (Input_GetMouseDeltaX() != 0.0 || Input_GetMouseDeltaY() != 0.0)
    {
        char buffer[128];

        snprintf(
            buffer,
            sizeof(buffer),
            "Polling mouse delta: dx=%f, dy=%f",
            Input_GetMouseDeltaX(),
            Input_GetMouseDeltaY()
        );

        print_info(buffer);
    }

    if (Input_GetScrollY() != 0.0)
    {
        char buffer[128];

        snprintf(
            buffer,
            sizeof(buffer),
            "Polling mouse scroll: y=%f",
            Input_GetScrollY()
        );

        print_info(buffer);
    }
}


void LITEC_Update()
{
    /*
        Kopioidaan nykyinen input-tila previous-tilaksi ennen kuin
        glfwPollEvents() käsittelee uudet callbackit.
    */
    Input_BeginFrame();

    glfwPollEvents();

    Window_Update(window);

    LITEC_HandleInput();

    /*
        Tähän tulee myöhemmin pelin varsinainen päivityslogiikka.

        Huom:
        GuiLayerin päivitys/renderöinti tehdään tällä hetkellä LITEC_Render()
        -funktiossa, jotta Nuklear piirretään vasta glClear-kutsun jälkeen.
    */
}


void LITEC_Render()
{
    if (window == NULL)
    {
        return;
    }

    /*
        Ensin tyhjennetään ruutu.
        Window_Render sisältää tällä hetkellä glViewport, glClearColor ja glClear.
    */
    Window_Render(window);

    /*
        Tässä vaiheessa deltaTime on vielä 0.0f.
        Myöhemmin tähän voidaan tehdä oikea ajastus.
    */
    float deltaTime = 0.0f;

    /*
        Piirretään/päivitetään layerit vasta Window_Renderin jälkeen.

        Tämä on tärkeää Nuklearille:
            - Window_Render tekee glClear-kutsun
            - GuiLayer piirtää Nuklear GUI:n
            - glfwSwapBuffers näyttää lopputuloksen
    */
    for (unsigned int i = 0; i < LayerStack_GetCount(&layerStack); i++)
    {
        Layer* layer = LayerStack_GetLayer(&layerStack, i);

        if (layer != NULL && layer->OnUpdate != NULL)
        {
            layer->OnUpdate(layer, deltaTime);
        }
    }

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