#ifndef LITEC_RENDERER_H
#define LITEC_RENDERER_H

typedef enum LitecRendererBackend
{
    LITEC_RENDERER_BACKEND_NONE = 0,
    LITEC_RENDERER_BACKEND_OPENGL
} LitecRendererBackend;

int LitecRenderer_Init(LitecRendererBackend backend);
void LitecRenderer_Shutdown(void);

void LitecRenderer_BeginFrame(void);
void LitecRenderer_Clear(float r, float g, float b, float a);
void LitecRenderer_EndFrame(void);

LitecRendererBackend LitecRenderer_GetBackend(void);

#endif