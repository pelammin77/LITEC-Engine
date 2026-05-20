#ifndef LITEC_INPUT_H
#define LITEC_INPUT_H

void Input_Init(void);
void Input_BeginFrame(void);

/*
    Keyboard input
*/
int Input_IsKeyDown(int keyCode);
int Input_IsKeyPressed(int keyCode);
int Input_IsKeyReleased(int keyCode);

void Input_SetKeyState(int keyCode, int isDown);

/*
    Mouse buttons
*/
int Input_IsMouseButtonDown(int button);
int Input_IsMouseButtonPressed(int button);
int Input_IsMouseButtonReleased(int button);

void Input_SetMouseButtonState(int button, int isDown);

/*
    Mouse position
*/
void Input_SetMousePosition(double x, double y);

double Input_GetMouseX(void);
double Input_GetMouseY(void);
double Input_GetMouseDeltaX(void);
double Input_GetMouseDeltaY(void);

/*
    Mouse scroll
*/
void Input_AddMouseScroll(double xoffset, double yoffset);

double Input_GetScrollX(void);
double Input_GetScrollY(void);

#endif /* LITEC_INPUT_H */