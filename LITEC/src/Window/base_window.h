#ifndef LITEC_WINDOW_H
#define LITEC_WINDOW_H

/*
    base_window.h

    General Litec window interface.

    Higher-level engine code should use this file instead of including
    platform-specific window headers directly.

    Current implementation still stores GLFW-specific data in the Window
    struct. Later this can be hidden behind an opaque pointer or moved into
    a backend-specific internal structure.
*/

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "../Platform/OpenGL/OpenGLContext.h"


typedef struct Window
{
    GLFWwindow* glfwWindow;

    int width;
    int height;
    const char* title;

    OpenGLContext graphicsContext;

} Window;


Window* Window_Create(int width, int height, const char* title);
void Window_Destroy(Window* window);
void Window_Update(Window* window);
void Window_Render(Window* window);

#endif /* LITEC_WINDOW_H */