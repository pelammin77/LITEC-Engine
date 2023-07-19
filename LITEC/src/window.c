

// window.c

#include"window.h"

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
    // Tee tarvittavat p�ivitystoiminnot t�ss�...
}

void Window_Render(Window* window) {
    // Tee tarvittavat render�intitoiminnot t�ss�...
}

