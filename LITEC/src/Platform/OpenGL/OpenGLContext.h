// OpenGLContext.h

#ifndef LITEC_OPENGL_CONTEXT_H
#define LITEC_OPENGL_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
    OpenGLContext

    Handles OpenGL-specific context initialization.
    This includes loading OpenGL functions with GLAD
    and printing basic OpenGL information.

    The actual window is still created elsewhere,
    for example in Window.c using GLFW.
*/

struct GLFWwindow;

typedef struct OpenGLContext
{
    struct GLFWwindow* window;
    int initialized;
} OpenGLContext;

/*
    Initializes OpenGL context for the given GLFW window.

    Returns:
        1 on success
        0 on failure
*/
int OpenGLContext_Init(OpenGLContext* context, struct GLFWwindow* window);

/*
    Swaps front and back buffers.

    For now this uses GLFW internally.
*/
void OpenGLContext_SwapBuffers(OpenGLContext* context);

/*
    Shuts down the OpenGL context wrapper.

    This does not destroy the GLFW window.
*/
void OpenGLContext_Shutdown(OpenGLContext* context);

#ifdef __cplusplus
}
#endif

#endif /* LITEC_OPENGL_CONTEXT_H */