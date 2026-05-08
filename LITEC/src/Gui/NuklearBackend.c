#include "NuklearBackend.h"

#include <stdio.h>

/*
    Nuklear implementation should be included in exactly ONE .c file.

    Later this file can contain something like:

        #define NK_INCLUDE_FIXED_TYPES
        #define NK_INCLUDE_STANDARD_IO
        #define NK_INCLUDE_STANDARD_VARARGS
        #define NK_INCLUDE_DEFAULT_ALLOCATOR
        #define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
        #define NK_INCLUDE_FONT_BAKING
        #define NK_INCLUDE_DEFAULT_FONT
        #define NK_IMPLEMENTATION
        #include "nuklear.h"

        #define NK_GLFW_GL3_IMPLEMENTATION
        #include "nuklear_glfw_gl3.h"

    For now this is only a clean skeleton.
*/

int NuklearBackend_Init(NuklearBackend* backend, struct GLFWwindow* window)
{
    if (backend == NULL)
    {
        return 0;
    }

    backend->window = window;
    backend->ctx = NULL;
    backend->initialized = 0;

    if (window == NULL)
    {
        return 0;
    }

    /*
        TODO:
        Initialize Nuklear GLFW/OpenGL backend here.

        Example later:

            backend->ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);

            struct nk_font_atlas* atlas;
            nk_glfw3_font_stash_begin(&atlas);
            nk_glfw3_font_stash_end();

            backend->initialized = 1;
    */

    backend->initialized = 1;

    return 1;
}

void NuklearBackend_BeginFrame(NuklearBackend* backend)
{
    if (backend == NULL || !backend->initialized)
    {
        return;
    }

    /*
        TODO:
        Start Nuklear input/frame.

        Example later:

            nk_glfw3_new_frame();
    */
}

void NuklearBackend_EndFrame(NuklearBackend* backend)
{
    if (backend == NULL || !backend->initialized)
    {
        return;
    }

    /*
        TODO:
        Render Nuklear GUI.

        Example later:

            nk_glfw3_render(
                NK_ANTI_ALIASING_ON,
                MAX_VERTEX_BUFFER,
                MAX_ELEMENT_BUFFER
            );
    */
}

void NuklearBackend_Shutdown(NuklearBackend* backend)
{
    if (backend == NULL)
    {
        return;
    }

    if (backend->initialized)
    {
        /*
            TODO:
            Shutdown Nuklear backend.

            Example later:

                nk_glfw3_shutdown();
        */
    }

    backend->window = NULL;
    backend->ctx = NULL;
    backend->initialized = 0;
}

struct nk_context* NuklearBackend_GetContext(NuklearBackend* backend)
{
    if (backend == NULL || !backend->initialized)
    {
        return NULL;
    }

    return backend->ctx;
}