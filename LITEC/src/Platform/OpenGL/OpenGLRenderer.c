// OpenGLRenderer.c

#include "Platform/OpenGL/OpenGLRenderer.h"

#include <glad/glad.h>

#include "Logger.h"


void OpenGLRenderer_Init(void)
{
    print_info("OpenGLRenderer initialized");

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
        Esimerkiksi:
        - viewportin päivitys
        - frame-kohtaisten tilastojen nollaus
        - render state setup
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
    print_info("OpenGLRenderer shutdown");

    /*
        Tänne myöhemmin:
        - glDeleteVertexArrays
        - glDeleteBuffers
        - glDeleteProgram
    */
}