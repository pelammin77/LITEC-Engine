// base_window.c

#include "base_window.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <glfw3.h>

#include "../Events/WindowEvent.h"
#include "../Events/EventDispatcher.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"


void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
{
    (void)glfwWindow;

    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_RESIZE, CATEGORY_WINDOW);
    event.width = width;
    event.height = height;

    EventDispatcher_DispatchEvent(&event.base_event);
}


void window_close_callback(GLFWwindow* glfwWindow)
{
    (void)glfwWindow;

    WindowEvent event;

    WindowEvent_Init(&event, EVENT_WINDOW_CLOSE, CATEGORY_WINDOW);

    EventDispatcher_DispatchEvent(&event.base_event);
}


Window* Window_Create(int width, int height, const char* title)
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

    glfwMakeContextCurrent(window->glfwWindow);

    // Ladataan GLAD vasta sen jälkeen, kun OpenGL-konteksti on aktiivinen.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");

        glfwDestroyWindow(window->glfwWindow);
        free(window);
        glfwTerminate();

        return NULL;
    }

    printf("GLAD initialized successfully\n");

    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);

    if (version) {
        printf("OpenGL version: %s\n", version);
    }
    else {
        printf("OpenGL version: NULL\n");
    }

    if (vendor) {
        printf("OpenGL vendor: %s\n", vendor);
    }
    else {
        printf("OpenGL vendor: NULL\n");
    }

    if (renderer) {
        printf("OpenGL renderer: %s\n", renderer);
    }
    else {
        printf("OpenGL renderer: NULL\n");
    }

    // Alustava taustaväri.
    glViewport(0, 0, width, height);
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


void Window_Destroy(Window* window)
{
    if (window) {
        if (window->glfwWindow) {
            glfwDestroyWindow(window->glfwWindow);
            window->glfwWindow = NULL;
        }

        free(window);
    }

    glfwTerminate();
}


void Window_Update(Window* window)
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


void Window_Render(Window* window)
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


void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
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