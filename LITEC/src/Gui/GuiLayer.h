//GuiLayer.h

#ifndef GUILAYER_H
#define GUILAYER_H

#include "../Layer.h"
#include <glfw3.h>
#include "NuklearBackend.h"



typedef struct {
	Layer base;
	NuklearBackend backend;
	GLFWwindow* window;
} GuiLayer;



Layer* GuiLayer_Create(GLFWwindow* window);
void GuiLayer_Destroy(Layer* layer);
static void GuiLayer_DrawDebugPanel(struct nk_context* ctx);

#endif