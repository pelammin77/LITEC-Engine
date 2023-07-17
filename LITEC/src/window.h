
#ifndef WINDOW_H
#define WINDOW_H

// Window.h


#include <glfw3.h>

typedef struct {
    GLFWwindow* glfwWindow;
    int width;
    int height;
    const char* title;
} Window;

Window* Window_Create(int width, int height, const char* title);
void Window_Destroy(Window* window);
void Window_Update(Window* window);
void Window_Render(Window* window);


#endif