#include "OpenGLTest.h"

#include <glad/glad.h>
#include <stdio.h>

void OpenGLTest_Init(void)
{
    printf("OpenGLTest_Init called\n");

    /*
        Tänne myöhemmin:
        - vertex data
        - VAO
        - VBO
        - shaderien luonti
    */
}

void OpenGLTest_Render(void)
{
    /*
        Tänne myöhemmin:
        - glUseProgram(...)
        - glBindVertexArray(...)
        - glDrawArrays(GL_TRIANGLES, 0, 3)
    */
}

void OpenGLTest_Shutdown(void)
{
    printf("OpenGLTest_Shutdown called\n");

    /*
        Tänne myöhemmin:
        - glDeleteVertexArrays
        - glDeleteBuffers
        - glDeleteProgram
    */
}