// OpenGLRenderer.c

#include "Platform/OpenGL/OpenGLRenderer.h"

#include <glad/glad.h>
#include <stdio.h>

void OpenGLRenderer_Init(void)
{
    printf("OpenGLRenderer_Init called\n");

    /*
        Tänne myöhemmin:
        - vertex data
        - VAO
        - VBO
        - shaderien luonti
    */
}

void OpenGLRenderer_BeginFrame(void)
{
    /*
        Tänne myöhemmin voidaan lisätä OpenGL frame setup.
    */
}

void OpenGLRenderer_Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer_Render(void)
{
    /*
        Tänne myöhemmin:
        - glUseProgram(...)
        - glBindVertexArray(...)
        - glDrawArrays(GL_TRIANGLES, 0, 3)
    */
}

void OpenGLRenderer_EndFrame(void)
{
    /*
        Tänne myöhemmin voidaan lisätä frame cleanup.
    */
}

void OpenGLRenderer_Shutdown(void)
{
    printf("OpenGLRenderer_Shutdown called\n");

    /*
        Tänne myöhemmin:
        - glDeleteVertexArrays
        - glDeleteBuffers
        - glDeleteProgram
    */
}