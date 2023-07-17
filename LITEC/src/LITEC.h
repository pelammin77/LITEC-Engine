// LITEC.h

#ifndef LITEC_H
#define LITEC_H

#ifdef LITEC_EXPORTS
#define LITEC_API __declspec(dllexport)
#else
#define LITEC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	LITEC_API void LITEC_Init(void);
	LITEC_API int LITEC_Running(void);
	LITEC_API void LITEC_HandleInput(void);
	LITEC_API void LITEC_Update(void);
	LITEC_API void LITEC_Render(void);
	LITEC_API void LITEC_Shutdown(void);

#ifdef __cplusplus
}
#endif

#endif
