#include "Input.h"

#include <string.h>

#define LITEC_MAX_KEYS 512
#define LITEC_MAX_MOUSE_BUTTONS 16

static int keyStates[LITEC_MAX_KEYS];
static int previousKeyStates[LITEC_MAX_KEYS];

static int mouseButtonStates[LITEC_MAX_MOUSE_BUTTONS];
static int previousMouseButtonStates[LITEC_MAX_MOUSE_BUTTONS];

static double mouseX = 0.0;
static double mouseY = 0.0;

static double previousMouseX = 0.0;
static double previousMouseY = 0.0;

static double scrollX = 0.0;
static double scrollY = 0.0;


void Input_Init(void)
{
    memset(keyStates, 0, sizeof(keyStates));
    memset(previousKeyStates, 0, sizeof(previousKeyStates));

    memset(mouseButtonStates, 0, sizeof(mouseButtonStates));
    memset(previousMouseButtonStates, 0, sizeof(previousMouseButtonStates));

    mouseX = 0.0;
    mouseY = 0.0;

    previousMouseX = 0.0;
    previousMouseY = 0.0;

    scrollX = 0.0;
    scrollY = 0.0;
}


void Input_BeginFrame(void)
{
    memcpy(previousKeyStates, keyStates, sizeof(keyStates));

    memcpy(
        previousMouseButtonStates,
        mouseButtonStates,
        sizeof(mouseButtonStates)
    );

    previousMouseX = mouseX;
    previousMouseY = mouseY;

    scrollX = 0.0;
    scrollY = 0.0;
}


int Input_IsKeyDown(int keyCode)
{
    if (keyCode < 0 || keyCode >= LITEC_MAX_KEYS) {
        return 0;
    }

    return keyStates[keyCode] == 1;
}


int Input_IsKeyPressed(int keyCode)
{
    if (keyCode < 0 || keyCode >= LITEC_MAX_KEYS) {
        return 0;
    }

    return keyStates[keyCode] == 1 &&
        previousKeyStates[keyCode] == 0;
}


int Input_IsKeyReleased(int keyCode)
{
    if (keyCode < 0 || keyCode >= LITEC_MAX_KEYS) {
        return 0;
    }

    return keyStates[keyCode] == 0 &&
        previousKeyStates[keyCode] == 1;
}


void Input_SetKeyState(int keyCode, int isDown)
{
    if (keyCode < 0 || keyCode >= LITEC_MAX_KEYS) {
        return;
    }

    keyStates[keyCode] = isDown ? 1 : 0;
}


int Input_IsMouseButtonDown(int button)
{
    if (button < 0 || button >= LITEC_MAX_MOUSE_BUTTONS) {
        return 0;
    }

    return mouseButtonStates[button] == 1;
}


int Input_IsMouseButtonPressed(int button)
{
    if (button < 0 || button >= LITEC_MAX_MOUSE_BUTTONS) {
        return 0;
    }

    return mouseButtonStates[button] == 1 &&
        previousMouseButtonStates[button] == 0;
}


int Input_IsMouseButtonReleased(int button)
{
    if (button < 0 || button >= LITEC_MAX_MOUSE_BUTTONS) {
        return 0;
    }

    return mouseButtonStates[button] == 0 &&
        previousMouseButtonStates[button] == 1;
}


void Input_SetMouseButtonState(int button, int isDown)
{
    if (button < 0 || button >= LITEC_MAX_MOUSE_BUTTONS) {
        return;
    }

    mouseButtonStates[button] = isDown ? 1 : 0;
}


void Input_SetMousePosition(double x, double y)
{
    mouseX = x;
    mouseY = y;
}


double Input_GetMouseX(void)
{
    return mouseX;
}


double Input_GetMouseY(void)
{
    return mouseY;
}


double Input_GetMouseDeltaX(void)
{
    return mouseX - previousMouseX;
}


double Input_GetMouseDeltaY(void)
{
    return mouseY - previousMouseY;
}


void Input_AddMouseScroll(double xoffset, double yoffset)
{
    scrollX += xoffset;
    scrollY += yoffset;
}


double Input_GetScrollX(void)
{
    return scrollX;
}


double Input_GetScrollY(void)
{
    return scrollY;
}