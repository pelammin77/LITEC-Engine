// This file is part of LITEC, a lightweight game engine.
// Copyright (c) 2024-2025, Lightbend, Inc. and the LITEC contributors
// For the full copyright and license information, please view the LICENSE file
// that was distributed with this source code.
//
// GuiLayer.c

#include "GuiLayer.h"
#include "Logger.h"
#include <stdlib.h>
#include "nuklear.h"


static void GuiLayer_OnAttach(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (guiLayer->window == NULL)
    {
        print_error("GuiLayer attach failed: GLFWwindow is NULL");
        return;
    }

    if (!NuklearBackend_Init(&guiLayer->backend, guiLayer->window))
    {
        print_error("GuiLayer attach failed: NuklearBackend initialization failed");
        return;
    }

    print_info("GuiLayer attached");
}


static void GuiLayer_OnDetach(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    NuklearBackend_Shutdown(&guiLayer->backend);

    print_info("GuiLayer detached");
}

static void GuiLayer_DrawDebugPanel(struct nk_context* ctx)
{
   // print_info("Drawing Litec Debug Panel");    
    static int showGrid = 1;
    static int showConsole = 1;
    static float testValue = 0.5f;

    if (ctx == NULL)
    {
        return;
    }

    if (nk_begin(
        ctx,
        "Litec Debug Panel",
        nk_rect(50, 50, 260, 220),
        NK_WINDOW_BORDER |
        NK_WINDOW_MOVABLE |
        NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE |
        NK_WINDOW_TITLE))
    {
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Hello from Nuklear", NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 25, 1);
        nk_checkbox_label(ctx, "Show grid", &showGrid);

        nk_layout_row_dynamic(ctx, 25, 1);
        nk_checkbox_label(ctx, "Show console", &showConsole);

        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_float(ctx, "Value", 0.0f, &testValue, 1.0f, 0.01f, 0.005f);

        nk_layout_row_dynamic(ctx, 30, 1);
        if (nk_button_label(ctx, "Test Button"))
        {
            print_info("Litec Debug Panel button clicked");
        }
    }

    nk_end(ctx);
}
static void GuiLayer_OnUpdate(Layer* layer, float deltaTime)
{
    (void)deltaTime;

    if (layer == NULL)
    {
        return;
    }

    static int printed = 0;

    if (!printed)
    {
        print_info("GuiLayer update running");
        printed = 1;
    }


    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (!guiLayer->backend.initialized)
    {
        return;
    }

    NuklearBackend_BeginFrame(&guiLayer->backend);

    struct nk_context* ctx = NuklearBackend_GetContext(&guiLayer->backend);

    if (ctx != NULL)
    {
        GuiLayer_DrawDebugPanel(ctx);
    }

    NuklearBackend_EndFrame(&guiLayer->backend);
}


static void GuiLayer_OnEvent(Layer* layer, Event* event)
{
    (void)layer;

    if (event == NULL)
    {
        return;
    }

    if (event->type == EVENT_MOUSE_MOVED)
    {
        print_info("GuiLayer received mouse moved event");

        /*
            Tätä ei kannata vielä ottaa pysyvästi käyttöön ennen kuin
            Nuklearin input-logiikka on mukana.

            Myöhemmin:
                - jos GUI haluaa hiiren, event->handled = 1
                - jos ei halua, event kulkee seuraaville layereille
        */

        // event->handled = 1;
    }
    else if (event->type == EVENT_KEY_PRESSED)
    {
        print_info("GuiLayer received key pressed event");
    }
    else
    {
        print_info("GuiLayer received event");
    }
}


Layer* GuiLayer_Create(GLFWwindow* window)
{
    GuiLayer* guiLayer = (GuiLayer*)malloc(sizeof(GuiLayer));

    if (guiLayer == NULL)
    {
        print_error("Failed to create GuiLayer");
        return NULL;
    }

    Layer* layer = &guiLayer->base;

    guiLayer->window = window;

    guiLayer->backend.window = NULL;
    guiLayer->backend.ctx = NULL;
    guiLayer->backend.initialized = 0;

    Layer_Init(layer, "GuiLayer", LAYER_TYPE_OVERLAY);

    layer->OnAttach = GuiLayer_OnAttach;
    layer->OnDetach = GuiLayer_OnDetach;
    layer->OnUpdate = GuiLayer_OnUpdate;
    layer->OnEvent = GuiLayer_OnEvent;

    print_info("GuiLayer created");

    return layer;
}


void GuiLayer_Destroy(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (layer->OnDetach != NULL)
    {
        layer->OnDetach(layer);
    }

    print_info("GuiLayer destroyed");

    free(guiLayer);
}