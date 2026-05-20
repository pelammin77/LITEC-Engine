#ifndef LITEC_GLFW_INPUT_MAP_H
#define LITEC_GLFW_INPUT_MAP_H

/*
    GLFWInputMap.h

    Converts GLFW-specific input codes to Litec engine input codes.

    This file belongs to the GLFW platform/backend layer.
    The rest of the engine should use Litec's own KeyCodes.h and
    MouseCodes.h instead of GLFW_KEY_* or GLFW_MOUSE_BUTTON_* values.
*/

#include "../../Input/KeyCodes.h"
#include "../../Input/MouseCodes.h"


/*
    Converts a GLFW key code to a Litec key code.

    Example:
        GLFW_KEY_A            -> LITEC_KEY_A
        GLFW_KEY_LEFT_CONTROL -> LITEC_KEY_LEFT_CONTROL
*/
LitecKeyCode GLFWInputMap_ToLitecKey(int glfwKey);


/*
    Converts a GLFW mouse button code to a Litec mouse button code.

    Example:
        GLFW_MOUSE_BUTTON_LEFT  -> LITEC_MOUSE_BUTTON_LEFT
        GLFW_MOUSE_BUTTON_RIGHT -> LITEC_MOUSE_BUTTON_RIGHT
*/
LitecMouseButton GLFWInputMap_ToLitecMouseButton(int glfwButton);


#endif /* LITEC_GLFW_INPUT_MAP_H */