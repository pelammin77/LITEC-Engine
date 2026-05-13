// This file is part of LITEC, a lightweight game engine.
// Copyright (c) 2024-2025, Lightbend, Inc. and the LITEC contributors
// For the full copyright and license information, please view the LICENSE file
// that was distributed with this source code.
//
// GuiLayer.c

#include "GuiLayer.h"
#include "Logger.h"

#include <stdlib.h>


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


static void GuiLayer_OnUpdate(Layer* layer, float deltaTime)
{
    (void)deltaTime;

    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (!guiLayer->backend.initialized)
    {
        return;
    }

    /*
        Tässä alkaa myöhemmin Nuklearin frame.

        Rakenne tulee olemaan:

            NuklearBackend_BeginFrame(...)

            // Täällä rakennetaan GUI:
            // - Litec Debug Panel
            // - napit
            // - checkboxit
            // - sliderit
            // - myöhemmin editoripaneelit

            NuklearBackend_EndFrame(...)

        Tällä hetkellä backend-funktiot ovat vielä tyhjiä/skeleton-vaiheessa,
        mutta kutsuketju on nyt oikeassa paikassa.
    */

    NuklearBackend_BeginFrame(&guiLayer->backend);

    /*
        Seuraavassa vaiheessa tänne tulee esimerkiksi:

            struct nk_context* ctx = NuklearBackend_GetContext(&guiLayer->backend);

            if (ctx != NULL)
            {
                GuiLayer_DrawDebugPanel(ctx);
            }
    */

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