#ifndef LITEC_OPENGL_RENDERER_H
#define LITEC_OPENGL_RENDERER_H

// OpenGLRenderer.h

void OpenGLRenderer_Init(void);

void OpenGLRenderer_BeginFrame(void);
void OpenGLRenderer_Clear(float r, float g, float b, float a);
void OpenGLRenderer_Render(void);
void OpenGLRenderer_EndFrame(void);

void OpenGLRenderer_Shutdown(void);

#endif