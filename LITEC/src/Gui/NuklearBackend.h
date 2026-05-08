#ifndef LITEC_NUKLEAR_BACKEND_H
#define LITEC_NUKLEAR_BACKEND_H

#ifdef __cplusplus
extern "C" {
#endif

/*
    NuklearBackend

    This module is responsible for connecting Nuklear GUI
    with the underlying windowing and rendering backend.

    Current planned backend:
        - GLFW
        - OpenGL 3+

    GuiLayer should use this backend instead of calling
    Nuklear/GLFW/OpenGL directly.
*/

struct GLFWwindow;
struct nk_context;

typedef struct NuklearBackend
{
    struct GLFWwindow* window;
    struct nk_context* ctx;
    int initialized;
} NuklearBackend;

/*
    Initializes Nuklear backend.

    Parameters:
        backend - pointer to backend instance
        window  - GLFW window used by Litec

    Returns:
        1 on success
        0 on failure
*/
int NuklearBackend_Init(NuklearBackend* backend, struct GLFWwindow* window);

/*
    Starts a new Nuklear frame.

    Should be called once per frame before creating GUI widgets.
*/
void NuklearBackend_BeginFrame(NuklearBackend* backend);

/*
    Ends the current Nuklear frame and renders GUI.

    Should be called once per frame after creating GUI widgets.
*/
void NuklearBackend_EndFrame(NuklearBackend* backend);

/*
    Shuts down Nuklear backend and releases resources.
*/
void NuklearBackend_Shutdown(NuklearBackend* backend);

/*
    Returns Nuklear context.

    GuiLayer can use this to build UI with Nuklear directly.
*/
struct nk_context* NuklearBackend_GetContext(NuklearBackend* backend);

#ifdef __cplusplus
}
#endif

#endif /* LITEC_NUKLEAR_BACKEND_H */