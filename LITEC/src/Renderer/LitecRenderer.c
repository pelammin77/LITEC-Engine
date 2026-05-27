// LitecRenderer.c

#include "LitecRenderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Logger.h"

static LitecRendererBackend s_backend = LITEC_RENDERER_BACKEND_NONE;
static int s_initialized = 0;


int LitecRenderer_Init(LitecRendererBackend backend)
{
    if (s_initialized)
    {
        return 1;
    }

    if (backend == LITEC_RENDERER_BACKEND_NONE)
    {
        return 0;
    }

    s_backend = backend;
    s_initialized = 1;

    return 1;
}


void LitecRenderer_Shutdown(void)
{
    if (!s_initialized)
    {
        return;
    }

    s_backend = LITEC_RENDERER_BACKEND_NONE;
    s_initialized = 0;
}


void LitecRenderer_BeginFrame(void)
{
    if (!s_initialized)
    {
        return;
    }
}


void LitecRenderer_Clear(float r, float g, float b, float a)
{
    (void)r;
    (void)g;
    (void)b;
    (void)a;

    if (!s_initialized)
    {
        return;
    }
}


void LitecRenderer_EndFrame(void)
{
    if (!s_initialized)
    {
        return;
    }
}


LitecRendererBackend LitecRenderer_GetBackend(void)
{
    return s_backend;
}