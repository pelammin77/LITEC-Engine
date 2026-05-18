#ifndef LITEC_GLFW_WINDOW_H
#define LITEC_GLFW_WINDOW_H

/*
    GLFWWindow.h

    GLFW-specific window backend for Litec.

    This file belongs to the platform/backend layer.
    The rest of the engine should normally use Window/base_window.h
    instead of including this file directly.
*/

#include "../../Window/base_window.h"

/*
    Creates a GLFW-backed Litec window.

    Internally this implementation is responsible for:
    - initializing GLFW
    - creating the native GLFW window
    - initializing the OpenGL context
    - registering GLFW callbacks
*/
Window* GLFWWindow_Create(int width, int height, const char* title);

/*
    Destroys a GLFW-backed Litec window.

    Internally this implementation is responsible for:
    - shutting down the OpenGL context
    - destroying the GLFW window
    - terminating GLFW
*/
void GLFWWindow_Destroy(Window* window);

/*
    Updates internal window state.

    For the GLFW backend this currently checks the framebuffer size
    and updates the stored width and height values.
*/
void GLFWWindow_Update(Window* window);

/*
    Renders / clears the GLFW-backed window.

    At the moment this still contains temporary OpenGL clear logic.
    Later this should probably move more clearly into the renderer.
*/
void GLFWWindow_Render(Window* window);


/*
    GLFW callback functions.

    These are backend-internal callbacks registered with GLFW.
    They are declared here so GLFWWindow.c can keep the callback
    registration clear.

    Later, these could be moved to a private/internal header if needed.
*/

void GLFWWindow_FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);

void GLFWWindow_CloseCallback(GLFWwindow* glfwWindow);

void GLFWWindow_KeyCallback(
    GLFWwindow* glfwWindow,
    int key,
    int scancode,
    int action,
    int mods
);

void GLFWWindow_MousePositionCallback(
    GLFWwindow* glfwWindow,
    double xpos,
    double ypos
);

void GLFWWindow_MouseButtonCallback(
    GLFWwindow* glfwWindow,
    int button,
    int action,
    int mods
);

void GLFWWindow_MouseScrollCallback(
    GLFWwindow* glfwWindow,
    double xoffset,
    double yoffset
);

#endif /* LITEC_GLFW_WINDOW_H */