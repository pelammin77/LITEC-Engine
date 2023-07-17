// window.c

#include "window.h"

Window* Window_Create(int width, int height, const char* title) {
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
    // Tee tarvittavat päivitystoiminnot tässä...
}

void Window_Render(Window* window) {
    // Tee tarvittavat renderöintitoiminnot tässä...
}

