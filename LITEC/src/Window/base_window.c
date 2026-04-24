// base_window.c

#include"base_window.h"
#include <glad/glad.h>
#include<glfw3.h>
#include "../Events/WindowEvent.h"
#include "../Events/EventDispatcher.h"
#include "../Events/KeyEvent.h"
#include"../Events/MouseEvent.h"





void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
   // printf("framebuffer_size_callback called with width: %d, height: %d\n", width, height);
    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_RESIZE, CATEGORY_WINDOW);
    event.width = width;
    event.height = height;
    //send event 
    EventDispatcher_DispatchEvent(&event.base_event);
   


}


void window_close_callback(GLFWwindow* glfwWindow) {
    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_CLOSE, CATEGORY_WINDOW);

    //send event 
    EventDispatcher_DispatchEvent(&event.base_event);
   


}




Window* Window_Create(int width, int height, const char* title) {
    // Alusta GLFW-kirjasto.
    if (!glfwInit()) {
        // GLFW:n alustus epäonnistui.
        printf("GLFW initialization failed!\n");
        return NULL;
    }
    Window* window = malloc(sizeof(Window));
    window->width = width;
    window->height = height;
    window->title = title;
    
    window->glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
  
    if (!window->glfwWindow) {
        free(window);
        return NULL;
    } 
    glfwMakeContextCurrent(window->glfwWindow);
   // glfwSetWindowSizeLimits(window->glfwWindow, width, height, width, height);

     // Ladataan GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return NULL;
    }
    glClearColor(0.0f, 0.0f, 170.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glfwSetFramebufferSizeCallback(window->glfwWindow, framebuffer_size_callback);
    glfwSetWindowCloseCallback(window->glfwWindow, window_close_callback);
    glfwSetKeyCallback(window->glfwWindow, key_callback);
    glfwSetCursorPosCallback(window->glfwWindow, mouse_position_callback);
    glfwSetMouseButtonCallback(window->glfwWindow, mouse_button_callback);
    glfwSetScrollCallback(window->glfwWindow, mouse_scroll_callback);
    return window;
}

void Window_Destroy(Window* window) {
    if (window) {
        if (window->glfwWindow) {
            glfwDestroyWindow(window->glfwWindow);
        }
        free(window);
    }
}

void Window_Update(Window* window) {
    
   
    
    int width, height;
    glfwGetFramebufferSize(window->glfwWindow, &width, &height);

   
    if (window->width != width || window->height != height) {
        window->width = width;
        window->height = height;
      
       
    }
    
}

void Window_Render(Window* window) {
    glClear(GL_COLOR_BUFFER_BIT); // Tyhjennetään ikkuna.
    int width, height;
    
    glfwGetFramebufferSize(window->glfwWindow, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.0f, 0.0f, 170.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Tyhjennetään ikkuna.

}

void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    Event event;

    if (action == GLFW_PRESS) {
        KeyPressedEventData data;
        KeyEvent_CreatePressed(&event, &data, key, 0);

        // send event       
        EventDispatcher_DispatchEvent(&event);
    }

    if (action == GLFW_RELEASE) {
        KeyReleasedEventData data;
        KeyEvent_CreateReleased(&event, &data, key);

        // send event	   
        EventDispatcher_DispatchEvent(&event);
    }

    if (action == GLFW_REPEAT) {
        KeyPressedEventData data;
        KeyEvent_CreatePressed(&event, &data, key, 1);

        // send event
        EventDispatcher_DispatchEvent(&event);
    }


}
void mouse_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
    (void)glfwWindow;

    MouseMovedEvent event;
    MouseMovedEvent_Init(&event, xpos, ypos);

    EventDispatcher_DispatchEvent(&event.base_event);
}

void mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
    (void)mods;

    double x, y;
    glfwGetCursorPos(glfwWindow, &x, &y);

    if (action == GLFW_PRESS) {
        MouseButtonEvent event;
        MouseButtonPressedEvent_Init(&event, button, x, y);

        EventDispatcher_DispatchEvent(&event.base_event);
    }
    else if (action == GLFW_RELEASE) {
        MouseButtonEvent event;
        MouseButtonReleasedEvent_Init(&event, button, x, y);

        EventDispatcher_DispatchEvent(&event.base_event);
    }
}

void mouse_scroll_callback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
{
    (void)glfwWindow;

    MouseScrolledEvent event;
    MouseScrolledEvent_Init(&event, xoffset, yoffset);

    EventDispatcher_DispatchEvent(&event.base_event);
}

