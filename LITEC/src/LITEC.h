// LITEC.h

#ifndef LITEC_H
#define LITEC_H

#include "Window/base_window.h"


#ifdef LITEC_EXPORTS
#define LITEC_API __declspec(dllexport)
#else
#define LITEC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef Window LITEC_Window;

	LITEC_API void LITEC_Init(const char* title, int width, int height);
	LITEC_API int LITEC_Running(void);
	LITEC_API void LITEC_HandleInput(void);
	LITEC_API void LITEC_Update();
	LITEC_API void LITEC_Render(void);
	LITEC_API void LITEC_Shutdown(void);
	LITEC_API LITEC_Window* LITEC_CreateWindow(const char* title, int width, int height);
	LITEC_API void LITEC_DestroyWindow(LITEC_Window* window);

#ifdef __cplusplus
}
#endif

#endif
