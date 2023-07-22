// LITEC.c



#include <stdio.h>
#include "LITEC.h"
#include "Logger.h"
#include "Events/EngineEvent.h"
#include "Events/WindowEvent.h"
#include "Events/EventDispatcher.h"

static int running = 1;
static LITEC_Window* window = NULL;

void handleWindowOpenEvent(const Event* event) {
    // Tarkistetaan, että tapahtuma on oikean tyyppinen
    if (event->type == EVENT_WINDOW_OPEN) {
        print_info("LITEC Engine created new window");
       
    }

    if (event->type == EVENT_WINDOW_RESIZE) {
        // Tulosta uudet ikkunan mitat
        print_info("Window resized event");
        // printf("framebuffer_size_callback called with width: %d, height: %d\n", event.width, event.height);
        
        // Muuta sovelluksen asetuksia tarvittaessa...
    }
}

void handleWindowResizeEvent(const Event* event) {
    // Tarkista että tapahtuma on oikean tyyppinen
    if (event->type == EVENT_WINDOW_RESIZE) {
        // Tulosta uudet ikkunan mitat
        print_info("Window resized event triggered");
        // Muuta sovelluksen asetuksia tarvittaessa...
    }
}




void LITEC_Init(const char* title, int width, int height) {

    init_logger();
    EventDispatcher_Init();
    
    print_info("LITEC engine is starting. Welcome!\n");
    EventDispatcher_RegisterHandler(EVENT_WINDOW_RESIZE, handleWindowResizeEvent);
   
   
    EventDispatcher_RegisterHandler(EVENT_WINDOW_OPEN, handleWindowOpenEvent);
   

   
    //window = Window_Create(width, height,title);
    window = LITEC_CreateWindow(title, width, height);

    if (window == NULL)
    {
        print_fatal_error("Window creation failed!");
       
        return ;
    }
 }

int LITEC_Running() {
    return running;
}

void LITEC_HandleInput() {
    // T�h�n tulee my�hemmin sy�tteiden k�sittelykoodi.
}

void LITEC_Update() {
    glfwPollEvents();
    Window_Update(window);
    glfwSwapBuffers(window->glfwWindow);
    LITEC_HandleInput();




    // T�h�n tulee my�hemmin pelin p�ivityskoodi.
}

void LITEC_Render() {
    Window_Render(window);
    glfwSwapBuffers(window->glfwWindow); //lisäsin tämän rivin 

       }

void LITEC_Shutdown() {
    // Luo EngineEvent
    EngineEvent engineShutdownEvent;
    EngineEvent_Init(&engineShutdownEvent, EVENT_ENGINE_SHUTDOWN, CATEGORY_ENGINE);
    
    // Lähetä tapahtuma järjestelmässä eteenpäin
    EventDispatcher_DispatchEvent(&engineShutdownEvent.base_event);
    init_logger();

    print_info("LITEC engine is shutting down. Goodbye!\n");
    running = 0;
    close_logger();

}

LITEC_Window* LITEC_CreateWindow(const char* title, int width, int height) {
    
 
  

    LITEC_Window* window = Window_Create(width, height, title);

    // check that window is created 
    if (window != NULL) {
        WindowEvent event;
        WindowEvent_Init(&event, EVENT_WINDOW_OPEN, CATEGORY_WINDOW);
        EventDispatcher_DispatchEvent(&event.base_event);
        
           }

   



    return window;
}

void LITEC_DestroyWindow(LITEC_Window* window) {
    Window_Destroy(window);
}
