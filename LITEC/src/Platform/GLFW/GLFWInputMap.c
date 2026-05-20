// GLFWInputMap.c

#include "GLFWInputMap.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>


LitecKeyCode GLFWInputMap_ToLitecKey(int glfwKey)
{
    switch (glfwKey)
    {
        /*
            Printable keys
        */
        case GLFW_KEY_SPACE:         return LITEC_KEY_SPACE;
        case GLFW_KEY_APOSTROPHE:    return LITEC_KEY_APOSTROPHE;
        case GLFW_KEY_COMMA:         return LITEC_KEY_COMMA;
        case GLFW_KEY_MINUS:         return LITEC_KEY_MINUS;
        case GLFW_KEY_PERIOD:        return LITEC_KEY_PERIOD;
        case GLFW_KEY_SLASH:         return LITEC_KEY_SLASH;

        case GLFW_KEY_0:             return LITEC_KEY_0;
        case GLFW_KEY_1:             return LITEC_KEY_1;
        case GLFW_KEY_2:             return LITEC_KEY_2;
        case GLFW_KEY_3:             return LITEC_KEY_3;
        case GLFW_KEY_4:             return LITEC_KEY_4;
        case GLFW_KEY_5:             return LITEC_KEY_5;
        case GLFW_KEY_6:             return LITEC_KEY_6;
        case GLFW_KEY_7:             return LITEC_KEY_7;
        case GLFW_KEY_8:             return LITEC_KEY_8;
        case GLFW_KEY_9:             return LITEC_KEY_9;

        case GLFW_KEY_SEMICOLON:     return LITEC_KEY_SEMICOLON;
        case GLFW_KEY_EQUAL:         return LITEC_KEY_EQUAL;

        case GLFW_KEY_A:             return LITEC_KEY_A;
        case GLFW_KEY_B:             return LITEC_KEY_B;
        case GLFW_KEY_C:             return LITEC_KEY_C;
        case GLFW_KEY_D:             return LITEC_KEY_D;
        case GLFW_KEY_E:             return LITEC_KEY_E;
        case GLFW_KEY_F:             return LITEC_KEY_F;
        case GLFW_KEY_G:             return LITEC_KEY_G;
        case GLFW_KEY_H:             return LITEC_KEY_H;
        case GLFW_KEY_I:             return LITEC_KEY_I;
        case GLFW_KEY_J:             return LITEC_KEY_J;
        case GLFW_KEY_K:             return LITEC_KEY_K;
        case GLFW_KEY_L:             return LITEC_KEY_L;
        case GLFW_KEY_M:             return LITEC_KEY_M;
        case GLFW_KEY_N:             return LITEC_KEY_N;
        case GLFW_KEY_O:             return LITEC_KEY_O;
        case GLFW_KEY_P:             return LITEC_KEY_P;
        case GLFW_KEY_Q:             return LITEC_KEY_Q;
        case GLFW_KEY_R:             return LITEC_KEY_R;
        case GLFW_KEY_S:             return LITEC_KEY_S;
        case GLFW_KEY_T:             return LITEC_KEY_T;
        case GLFW_KEY_U:             return LITEC_KEY_U;
        case GLFW_KEY_V:             return LITEC_KEY_V;
        case GLFW_KEY_W:             return LITEC_KEY_W;
        case GLFW_KEY_X:             return LITEC_KEY_X;
        case GLFW_KEY_Y:             return LITEC_KEY_Y;
        case GLFW_KEY_Z:             return LITEC_KEY_Z;

        case GLFW_KEY_LEFT_BRACKET:  return LITEC_KEY_LEFT_BRACKET;
        case GLFW_KEY_BACKSLASH:     return LITEC_KEY_BACKSLASH;
        case GLFW_KEY_RIGHT_BRACKET: return LITEC_KEY_RIGHT_BRACKET;
        case GLFW_KEY_GRAVE_ACCENT:  return LITEC_KEY_GRAVE_ACCENT;

        /*
            Function and control keys
        */
        case GLFW_KEY_ESCAPE:        return LITEC_KEY_ESCAPE;
        case GLFW_KEY_ENTER:         return LITEC_KEY_ENTER;
        case GLFW_KEY_TAB:           return LITEC_KEY_TAB;
        case GLFW_KEY_BACKSPACE:     return LITEC_KEY_BACKSPACE;
        case GLFW_KEY_INSERT:        return LITEC_KEY_INSERT;
        case GLFW_KEY_DELETE:        return LITEC_KEY_DELETE;

        case GLFW_KEY_RIGHT:         return LITEC_KEY_RIGHT;
        case GLFW_KEY_LEFT:          return LITEC_KEY_LEFT;
        case GLFW_KEY_DOWN:          return LITEC_KEY_DOWN;
        case GLFW_KEY_UP:            return LITEC_KEY_UP;

        case GLFW_KEY_PAGE_UP:       return LITEC_KEY_PAGE_UP;
        case GLFW_KEY_PAGE_DOWN:     return LITEC_KEY_PAGE_DOWN;
        case GLFW_KEY_HOME:          return LITEC_KEY_HOME;
        case GLFW_KEY_END:           return LITEC_KEY_END;

        case GLFW_KEY_CAPS_LOCK:     return LITEC_KEY_CAPS_LOCK;
        case GLFW_KEY_SCROLL_LOCK:   return LITEC_KEY_SCROLL_LOCK;
        case GLFW_KEY_NUM_LOCK:      return LITEC_KEY_NUM_LOCK;
        case GLFW_KEY_PRINT_SCREEN:  return LITEC_KEY_PRINT_SCREEN;
        case GLFW_KEY_PAUSE:         return LITEC_KEY_PAUSE;

        /*
            Function keys
        */
        case GLFW_KEY_F1:            return LITEC_KEY_F1;
        case GLFW_KEY_F2:            return LITEC_KEY_F2;
        case GLFW_KEY_F3:            return LITEC_KEY_F3;
        case GLFW_KEY_F4:            return LITEC_KEY_F4;
        case GLFW_KEY_F5:            return LITEC_KEY_F5;
        case GLFW_KEY_F6:            return LITEC_KEY_F6;
        case GLFW_KEY_F7:            return LITEC_KEY_F7;
        case GLFW_KEY_F8:            return LITEC_KEY_F8;
        case GLFW_KEY_F9:            return LITEC_KEY_F9;
        case GLFW_KEY_F10:           return LITEC_KEY_F10;
        case GLFW_KEY_F11:           return LITEC_KEY_F11;
        case GLFW_KEY_F12:           return LITEC_KEY_F12;
        case GLFW_KEY_F13:           return LITEC_KEY_F13;
        case GLFW_KEY_F14:           return LITEC_KEY_F14;
        case GLFW_KEY_F15:           return LITEC_KEY_F15;
        case GLFW_KEY_F16:           return LITEC_KEY_F16;
        case GLFW_KEY_F17:           return LITEC_KEY_F17;
        case GLFW_KEY_F18:           return LITEC_KEY_F18;
        case GLFW_KEY_F19:           return LITEC_KEY_F19;
        case GLFW_KEY_F20:           return LITEC_KEY_F20;
        case GLFW_KEY_F21:           return LITEC_KEY_F21;
        case GLFW_KEY_F22:           return LITEC_KEY_F22;
        case GLFW_KEY_F23:           return LITEC_KEY_F23;
        case GLFW_KEY_F24:           return LITEC_KEY_F24;
        case GLFW_KEY_F25:           return LITEC_KEY_F25;

        /*
            Keypad
        */
        case GLFW_KEY_KP_0:          return LITEC_KEY_KP_0;
        case GLFW_KEY_KP_1:          return LITEC_KEY_KP_1;
        case GLFW_KEY_KP_2:          return LITEC_KEY_KP_2;
        case GLFW_KEY_KP_3:          return LITEC_KEY_KP_3;
        case GLFW_KEY_KP_4:          return LITEC_KEY_KP_4;
        case GLFW_KEY_KP_5:          return LITEC_KEY_KP_5;
        case GLFW_KEY_KP_6:          return LITEC_KEY_KP_6;
        case GLFW_KEY_KP_7:          return LITEC_KEY_KP_7;
        case GLFW_KEY_KP_8:          return LITEC_KEY_KP_8;
        case GLFW_KEY_KP_9:          return LITEC_KEY_KP_9;

        case GLFW_KEY_KP_DECIMAL:    return LITEC_KEY_KP_DECIMAL;
        case GLFW_KEY_KP_DIVIDE:     return LITEC_KEY_KP_DIVIDE;
        case GLFW_KEY_KP_MULTIPLY:   return LITEC_KEY_KP_MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT:   return LITEC_KEY_KP_SUBTRACT;
        case GLFW_KEY_KP_ADD:        return LITEC_KEY_KP_ADD;
        case GLFW_KEY_KP_ENTER:      return LITEC_KEY_KP_ENTER;
        case GLFW_KEY_KP_EQUAL:      return LITEC_KEY_KP_EQUAL;

        /*
            Modifier keys
        */
        case GLFW_KEY_LEFT_SHIFT:    return LITEC_KEY_LEFT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL:  return LITEC_KEY_LEFT_CONTROL;
        case GLFW_KEY_LEFT_ALT:      return LITEC_KEY_LEFT_ALT;
        case GLFW_KEY_LEFT_SUPER:    return LITEC_KEY_LEFT_SUPER;

        case GLFW_KEY_RIGHT_SHIFT:   return LITEC_KEY_RIGHT_SHIFT;
        case GLFW_KEY_RIGHT_CONTROL: return LITEC_KEY_RIGHT_CONTROL;
        case GLFW_KEY_RIGHT_ALT:     return LITEC_KEY_RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER:   return LITEC_KEY_RIGHT_SUPER;

        case GLFW_KEY_MENU:          return LITEC_KEY_MENU;

        default:                     return LITEC_KEY_UNKNOWN;
    }
}


LitecMouseButton GLFWInputMap_ToLitecMouseButton(int glfwButton)
{
    switch (glfwButton)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            return LITEC_MOUSE_BUTTON_LEFT;

        case GLFW_MOUSE_BUTTON_RIGHT:
            return LITEC_MOUSE_BUTTON_RIGHT;

        case GLFW_MOUSE_BUTTON_MIDDLE:
            return LITEC_MOUSE_BUTTON_MIDDLE;

        case GLFW_MOUSE_BUTTON_4:
            return LITEC_MOUSE_BUTTON_4;

        case GLFW_MOUSE_BUTTON_5:
            return LITEC_MOUSE_BUTTON_5;

        case GLFW_MOUSE_BUTTON_6:
            return LITEC_MOUSE_BUTTON_6;

        case GLFW_MOUSE_BUTTON_7:
            return LITEC_MOUSE_BUTTON_7;

        case GLFW_MOUSE_BUTTON_8:
            return LITEC_MOUSE_BUTTON_8;

        default:
            return LITEC_MOUSE_BUTTON_UNKNOWN;
    }
}