

// window.c

#include"base_window.h"
#include <glad/glad.h>
#include<glfw3.h>
#include"WindowEvent.h"





void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
   // printf("framebuffer_size_callback called with width: %d, height: %d\n", width, height);
    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_RESIZE, CATEGORY_WINDOW);
    event.width = width;
    event.height = height;
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


