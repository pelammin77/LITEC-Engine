// KeyCodes.h

#ifndef LITEC_KEY_CODES_H
#define LITEC_KEY_CODES_H

/*
    Litec Key Codes

    These are Litec engine internal/public key codes.

    Important:
    - Do not expose GLFW_KEY_*, Win32 VK_*, X11 keysyms, etc. to engine users.
    - Platform/backend code should convert native key codes into these Litec key codes.
    - Input polling and key events should use these values.
*/

typedef enum LitecKeyCode
{
    LITEC_KEY_UNKNOWN = 0,

    /*
        Printable keys
    */
    LITEC_KEY_SPACE,
    LITEC_KEY_APOSTROPHE,      /* ' */
    LITEC_KEY_COMMA,           /* , */
    LITEC_KEY_MINUS,           /* - */
    LITEC_KEY_PERIOD,          /* . */
    LITEC_KEY_SLASH,           /* / */

    LITEC_KEY_0,
    LITEC_KEY_1,
    LITEC_KEY_2,
    LITEC_KEY_3,
    LITEC_KEY_4,
    LITEC_KEY_5,
    LITEC_KEY_6,
    LITEC_KEY_7,
    LITEC_KEY_8,
    LITEC_KEY_9,

    LITEC_KEY_SEMICOLON,       /* ; */
    LITEC_KEY_EQUAL,           /* = */

    LITEC_KEY_A,
    LITEC_KEY_B,
    LITEC_KEY_C,
    LITEC_KEY_D,
    LITEC_KEY_E,
    LITEC_KEY_F,
    LITEC_KEY_G,
    LITEC_KEY_H,
    LITEC_KEY_I,
    LITEC_KEY_J,
    LITEC_KEY_K,
    LITEC_KEY_L,
    LITEC_KEY_M,
    LITEC_KEY_N,
    LITEC_KEY_O,
    LITEC_KEY_P,
    LITEC_KEY_Q,
    LITEC_KEY_R,
    LITEC_KEY_S,
    LITEC_KEY_T,
    LITEC_KEY_U,
    LITEC_KEY_V,
    LITEC_KEY_W,
    LITEC_KEY_X,
    LITEC_KEY_Y,
    LITEC_KEY_Z,

    LITEC_KEY_LEFT_BRACKET,    /* [ */
    LITEC_KEY_BACKSLASH,       /* \ */
    LITEC_KEY_RIGHT_BRACKET,   /* ] */
    LITEC_KEY_GRAVE_ACCENT,    /* ` */

    /*
        Non-US keyboard keys
    */
    LITEC_KEY_WORLD_1,
    LITEC_KEY_WORLD_2,

    /*
        Function keys
    */
    LITEC_KEY_ESCAPE,
    LITEC_KEY_ENTER,
    LITEC_KEY_TAB,
    LITEC_KEY_BACKSPACE,
    LITEC_KEY_INSERT,
    LITEC_KEY_DELETE,

    LITEC_KEY_RIGHT,
    LITEC_KEY_LEFT,
    LITEC_KEY_DOWN,
    LITEC_KEY_UP,

    LITEC_KEY_PAGE_UP,
    LITEC_KEY_PAGE_DOWN,
    LITEC_KEY_HOME,
    LITEC_KEY_END,

    LITEC_KEY_CAPS_LOCK,
    LITEC_KEY_SCROLL_LOCK,
    LITEC_KEY_NUM_LOCK,
    LITEC_KEY_PRINT_SCREEN,
    LITEC_KEY_PAUSE,

    LITEC_KEY_F1,
    LITEC_KEY_F2,
    LITEC_KEY_F3,
    LITEC_KEY_F4,
    LITEC_KEY_F5,
    LITEC_KEY_F6,
    LITEC_KEY_F7,
    LITEC_KEY_F8,
    LITEC_KEY_F9,
    LITEC_KEY_F10,
    LITEC_KEY_F11,
    LITEC_KEY_F12,
    LITEC_KEY_F13,
    LITEC_KEY_F14,
    LITEC_KEY_F15,
    LITEC_KEY_F16,
    LITEC_KEY_F17,
    LITEC_KEY_F18,
    LITEC_KEY_F19,
    LITEC_KEY_F20,
    LITEC_KEY_F21,
    LITEC_KEY_F22,
    LITEC_KEY_F23,
    LITEC_KEY_F24,
    LITEC_KEY_F25,

    /*
        Keypad
    */
    LITEC_KEY_KP_0,
    LITEC_KEY_KP_1,
    LITEC_KEY_KP_2,
    LITEC_KEY_KP_3,
    LITEC_KEY_KP_4,
    LITEC_KEY_KP_5,
    LITEC_KEY_KP_6,
    LITEC_KEY_KP_7,
    LITEC_KEY_KP_8,
    LITEC_KEY_KP_9,

    LITEC_KEY_KP_DECIMAL,
    LITEC_KEY_KP_DIVIDE,
    LITEC_KEY_KP_MULTIPLY,
    LITEC_KEY_KP_SUBTRACT,
    LITEC_KEY_KP_ADD,
    LITEC_KEY_KP_ENTER,
    LITEC_KEY_KP_EQUAL,

    /*
        Modifier keys
    */
    LITEC_KEY_LEFT_SHIFT,
    LITEC_KEY_LEFT_CONTROL,
    LITEC_KEY_LEFT_ALT,
    LITEC_KEY_LEFT_SUPER,

    LITEC_KEY_RIGHT_SHIFT,
    LITEC_KEY_RIGHT_CONTROL,
    LITEC_KEY_RIGHT_ALT,
    LITEC_KEY_RIGHT_SUPER,

    LITEC_KEY_MENU,

    /*
        Keep this as the last real value.
        It can be used for array sizes in the input system.
    */
    LITEC_KEY_COUNT

} LitecKeyCode;

#endif /* LITEC_KEY_CODES_H */