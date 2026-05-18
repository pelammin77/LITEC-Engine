// base_window.c

#include "base_window.h"

#include "../Platform/GLFW/GLFWWindow.h"


Window* Window_Create(int width, int height, const char* title)
{
    return GLFWWindow_Create(width, height, title);
}


void Window_Destroy(Window* window)
{
    GLFWWindow_Destroy(window);
}


void Window_Update(Window* window)
{
    GLFWWindow_Update(window);
}


void Window_Render(Window* window)
{
    GLFWWindow_Render(window);
}