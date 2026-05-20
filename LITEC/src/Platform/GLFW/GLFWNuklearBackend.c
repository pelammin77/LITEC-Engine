// This file is part of LITEC, a lightweight game engine.
// Copyright (c) 2024-2025, Lightbend, Inc. and the LITEC contributors
// For the full copyright and license information, please view the LICENSE file
// that was distributed with this source code.
//
// NuklearBackend.c

//#include "NuklearBackend.h"

#include "Gui/NuklearBackend.h"

#include <stdio.h>
#include <string.h>

#include <glad/glad.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "Logger.h"

/*
    Nuklear implementation must be included in exactly ONE .c file.

    This file connects:
        - Nuklear
        - GLFW
        - OpenGL 3
*/

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

#define LITEC_NK_MAX_VERTEX_BUFFER  (512 * 1024)
#define LITEC_NK_MAX_ELEMENT_BUFFER (128 * 1024)

/*
    First version uses one global Nuklear GLFW backend instance.

    This is fine while Litec has one main window.
    Later, if multiple windows are supported, this can be moved
    into the NuklearBackend struct.
*/
static struct nk_glfw s_nuklearGlfw;


int NuklearBackend_Init(NuklearBackend* backend, struct GLFWwindow* window)
{
    if (backend == NULL)
    {
        print_error("NuklearBackend_Init failed: backend is NULL");
        return 0;
    }

    backend->window = NULL;
    backend->ctx = NULL;
    backend->initialized = 0;

    if (window == NULL)
    {
        print_error("NuklearBackend_Init failed: window is NULL");
        return 0;
    }

    backend->window = window;

    memset(&s_nuklearGlfw, 0, sizeof(s_nuklearGlfw));

    /*
        Litec owns GLFW callbacks.

        We use NK_GLFW3_DEFAULT so Nuklear does not overwrite Litec's
        keyboard, mouse, scroll or window callbacks.

        Input will later be routed to Nuklear through Litec's own
        event/input system.
    */
    backend->ctx = nk_glfw3_init(
        &s_nuklearGlfw,
        window,
        NK_GLFW3_DEFAULT
    );

    if (backend->ctx == NULL)
    {
        print_error("NuklearBackend_Init failed: nk_glfw3_init returned NULL");
        backend->window = NULL;
        return 0;
    }

    /*
        Initialize Nuklear font atlas.

        For now we use Nuklear's default font.
    */
    struct nk_font_atlas* atlas = NULL;

    nk_glfw3_font_stash_begin(&s_nuklearGlfw, &atlas);
    nk_glfw3_font_stash_end(&s_nuklearGlfw);

    backend->initialized = 1;

    print_info("NuklearBackend initialized");

    return 1;
}


void NuklearBackend_BeginFrame(NuklearBackend* backend)
{
    if (backend == NULL || !backend->initialized)
    {
        return;
    }

    nk_glfw3_new_frame(&s_nuklearGlfw);
}


void NuklearBackend_EndFrame(NuklearBackend* backend)
{
    if (backend == NULL || !backend->initialized)
    {
        return;
    }

    nk_glfw3_render(
        &s_nuklearGlfw,
        NK_ANTI_ALIASING_ON,
        LITEC_NK_MAX_VERTEX_BUFFER,
        LITEC_NK_MAX_ELEMENT_BUFFER
    );
}


void NuklearBackend_Shutdown(NuklearBackend* backend)
{
    if (backend == NULL)
    {
        return;
    }

    if (backend->initialized)
    {
        nk_glfw3_shutdown(&s_nuklearGlfw);
        print_info("NuklearBackend shutdown");
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