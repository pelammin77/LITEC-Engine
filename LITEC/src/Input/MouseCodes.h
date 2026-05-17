#ifndef LITEC_MOUSE_CODES_H
#define LITEC_MOUSE_CODES_H

/*
    Litec Mouse Codes

    These are Litec engine internal/public mouse button codes.

    Important:
    - Do not expose GLFW_MOUSE_BUTTON_*, Win32 mouse button codes,
      X11 button codes, etc. to engine users.
    - Platform/backend code should convert native mouse button codes
      into these Litec mouse button codes.
    - Input polling and mouse events should use these values.
*/

typedef enum LitecMouseButton
{
    LITEC_MOUSE_BUTTON_UNKNOWN = 0,

    LITEC_MOUSE_BUTTON_LEFT,
    LITEC_MOUSE_BUTTON_RIGHT,
    LITEC_MOUSE_BUTTON_MIDDLE,

    LITEC_MOUSE_BUTTON_4,
    LITEC_MOUSE_BUTTON_5,
    LITEC_MOUSE_BUTTON_6,
    LITEC_MOUSE_BUTTON_7,
    LITEC_MOUSE_BUTTON_8,

    /*
        Keep this as the last real value.
        It can be used for array sizes in the input system.
    */
    LITEC_MOUSE_BUTTON_COUNT

} LitecMouseButton;

#endif /* LITEC_MOUSE_CODES_H */