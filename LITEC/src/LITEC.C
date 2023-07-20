// LITEC.c



#include <stdio.h>
#include "LITEC.h"
#include "Logger.h"
#include "Events/EngineEvent.h"
#include "Events/EventDispatcher.h"

static int running = 1;
static LITEC_Window* window = NULL;

void LITEC_Init(const char* title, int width, int height) {
    
    init_logger();
    print_info("LITEC engine is starting. Welcome!\n");

   
    //window = Window_Create(width, height,title);
    window = LITEC_CreateWindow(title, width, height);

    if (window == NULL)
    {
        print_fatal_error("Window creation failed!");
       
        return 1;
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
    
    print_info("LITEC engine creates window");

    return Window_Create(width, height, title);
}

void LITEC_DestroyWindow(LITEC_Window* window) {
    Window_Destroy(window);
}
