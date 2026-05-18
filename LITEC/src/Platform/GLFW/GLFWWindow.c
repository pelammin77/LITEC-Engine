// GLFWWindow.c

#include "GLFWWindow.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "../../Events/WindowEvent.h"
#include "../../Events/EventDispatcher.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"


void GLFWWindow_FramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height)
{
    (void)glfwWindow;

    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_RESIZE, CATEGORY_WINDOW);
    event.width = width;
    event.height = height;

    EventDispatcher_DispatchEvent(&event.base_event);
}


void GLFWWindow_CloseCallback(GLFWwindow* glfwWindow)
{
    (void)glfwWindow;

    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_CLOSE, CATEGORY_WINDOW);

    EventDispatcher_DispatchEvent(&event.base_event);
}


Window* GLFWWindow_Create(int width, int height, const char* title)
{
    // Alusta GLFW-kirjasto.
    if (!glfwInit()) {
        printf("GLFW initialization failed!\n");
        return NULL;
    }

    Window* window = malloc(sizeof(Window));
    if (!window) {
        printf("Failed to allocate Window memory!\n");
        glfwTerminate();
        return NULL;
    }

    window->width = width;
    window->height = height;
    window->title = title;
    window->glfwWindow = NULL;

    window->glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window->glfwWindow) {
        printf("Failed to create GLFW window!\n");
        free(window);
        glfwTerminate();
        return NULL;
    }

    /*
        OpenGL-alustus on Platform/OpenGL/OpenGLContext.c-tiedostossa.

        Tämä tekee:
        - glfwMakeContextCurrent(...)
        - gladLoadGLLoader(...)
        - OpenGL vendor / renderer / version -tulostukset
    */
    if (!OpenGLContext_Init(&window->graphicsContext, window->glfwWindow)) {
        printf("Failed to initialize OpenGL context!\n");

        glfwDestroyWindow(window->glfwWindow);
        free(window);
        glfwTerminate();

        return NULL;
    }

    // Alustava taustaväri.
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 170.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetFramebufferSizeCallback(
        window->glfwWindow,
        GLFWWindow_FramebufferSizeCallback
    );

    glfwSetWindowCloseCallback(
        window->glfwWindow,
        GLFWWindow_CloseCallback
    );

    glfwSetKeyCallback(
        window->glfwWindow,
        GLFWWindow_KeyCallback
    );

    glfwSetCursorPosCallback(
        window->glfwWindow,
        GLFWWindow_MousePositionCallback
    );

    glfwSetMouseButtonCallback(
        window->glfwWindow,
        GLFWWindow_MouseButtonCallback
    );

    glfwSetScrollCallback(
        window->glfwWindow,
        GLFWWindow_MouseScrollCallback
    );

    return window;
}


void GLFWWindow_Destroy(Window* window)
{
    if (window) {
        OpenGLContext_Shutdown(&window->graphicsContext);

        if (window->glfwWindow) {
            glfwDestroyWindow(window->glfwWindow);
            window->glfwWindow = NULL;
        }

        free(window);
    }

    glfwTerminate();
}


void GLFWWindow_Update(Window* window)
{
    if (!window || !window->glfwWindow) {
        return;
    }

    int width, height;
    glfwGetFramebufferSize(window->glfwWindow, &width, &height);

    if (window->width != width || window->height != height) {
        window->width = width;
        window->height = height;
    }
}


void GLFWWindow_Render(Window* window)
{
    if (!window || !window->glfwWindow) {
        return;
    }

    int width, height;
    glfwGetFramebufferSize(window->glfwWindow, &width, &height);

    glViewport(0, 0, width, height);

    // Testiväri: tummahko sininen.
    glClearColor(0.0f, 0.0f, 170.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void GLFWWindow_KeyCallback(
    GLFWwindow* glfwWindow,
    int key,
    int scancode,
    int action,
    int mods
)
{
    (void)glfwWindow;
    (void)scancode;
    (void)mods;

    Event event;

    if (action == GLFW_PRESS) {
        KeyPressedEventData data;
        KeyEvent_CreatePressed(&event, &data, key, 0);

        EventDispatcher_DispatchEvent(&event);
    }

    if (action == GLFW_RELEASE) {
        KeyReleasedEventData data;
        KeyEvent_CreateReleased(&event, &data, key);

        EventDispatcher_DispatchEvent(&event);
    }

    if (action == GLFW_REPEAT) {
        KeyPressedEventData data;
        KeyEvent_CreatePressed(&event, &data, key, 1);

        EventDispatcher_DispatchEvent(&event);
    }
}


void GLFWWindow_MousePositionCallback(
    GLFWwindow* glfwWindow,
    double xpos,
    double ypos
)
{
    (void)glfwWindow;

    MouseMovedEvent event;
    MouseMovedEvent_Init(&event, xpos, ypos);

    EventDispatcher_DispatchEvent(&event.base_event);
}


void GLFWWindow_MouseButtonCallback(
    GLFWwindow* glfwWindow,
    int button,
    int action,
    int mods
)
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


void GLFWWindow_MouseScrollCallback(
    GLFWwindow* glfwWindow,
    double xoffset,
    double yoffset
)
{
    (void)glfwWindow;

    MouseScrolledEvent event;
    MouseScrolledEvent_Init(&event, xoffset, yoffset);

    EventDispatcher_DispatchEvent(&event.base_event);
}