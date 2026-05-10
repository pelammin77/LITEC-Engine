// OpenGLContext.c

#include "OpenGLContext.h"

#include <stdio.h>

#include <glad/glad.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <glfw3.h>

#include "Logger.h"

int OpenGLContext_Init(OpenGLContext* context, struct GLFWwindow* window)
{
    if (context == NULL)
    {
        return 0;
    }

    context->window = window;
    context->initialized = 0;

    if (window == NULL)
    {
        print_error("OpenGLContext_Init failed: window is NULL");
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        print_error("Failed to initialize GLAD");
        return 0;
    }

    print_info("GLAD initialized successfully");

    print_info("OpenGL context initialized");
    printf("OpenGL Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Version:  %s\n", glGetString(GL_VERSION));

    context->initialized = 1;

    return 1;
}

void OpenGLContext_SwapBuffers(OpenGLContext* context)
{
    if (context == NULL || !context->initialized || context->window == NULL)
    {
        return;
    }

    glfwSwapBuffers(context->window);
}

void OpenGLContext_Shutdown(OpenGLContext* context)
{
    if (context == NULL)
    {
        return;
    }

    context->window = NULL;
    context->initialized = 0;

    print_info("OpenGL context shutdown");
}